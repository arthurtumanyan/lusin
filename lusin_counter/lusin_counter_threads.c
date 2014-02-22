/*
    Lusin is a simple traffic accounting software.
    Copyright (C) 2013  Arthur Tumanyan <arthurtumanyan@google.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "lusin_counter.h"
#include "lusin_counter_prototypes.h"
#include "lusin_counter_protocol.h"

static float traffic_summary[BPF_MAX_COUNT];

double return_tr_count(long traffic);
char * return_tr_measure(long traffic);

void *process_counter(void * tc) {

    int sz = 128;
    char msg[sz];

    long thread_c = (long) tc;
    char errbuf[PCAP_ERRBUF_SIZE];

    //    /* Now get a device */
    dev[thread_c] = globals.rules[thread_c].device;

    if (dev[thread_c] == NULL) {
        pthread_mutex_lock(&counter_mutex);
        snprintf(msg, sz, "%s: %s", __FUNCTION__, errbuf);
        writeToStoreLog(msg);
        goto exit_thread;
        pthread_mutex_unlock(&counter_mutex);

    }
    /* Get the network address and mask */
    pcap_lookupnet(dev[thread_c], &netp[thread_c], &maskp[thread_c], errbuf);

    /* open device for reading in promiscuous mode */
    descr[thread_c] = pcap_open_live(dev[thread_c], BUFSIZ, 1, 100, errbuf);
    if (descr[thread_c] == NULL) {
        pthread_mutex_lock(&counter_mutex);
        snprintf(msg, sz, "%s: %s", __FUNCTION__, errbuf);
        writeToStoreLog(msg);
        goto exit_thread;
        pthread_mutex_unlock(&counter_mutex);
    }

    /* Now we'll compile the filter expression*/
    pthread_mutex_lock(&counter_mutex);
    if (pcap_compile(descr[thread_c], &fp[thread_c], globals.rules[thread_c].filter, 0, netp[thread_c]) == -1) {
        snprintf(msg, sz, "%s: Incorrect rule, see 'man pcap; man tcpdump'", __FUNCTION__);
        writeToStoreLog(msg);
        goto exit_thread;
    }

    /* set the filter */
    if (pcap_setfilter(descr[thread_c], &fp[thread_c]) == -1) {
        snprintf(msg, sz, "%s: Unable to set filter", __FUNCTION__);
        writeToStoreLog(msg);
        goto exit_thread;
    } else {
        snprintf(msg, sz, "Activated rule #%ld", thread_c);
        writeToStoreLog(msg);
    }
    pthread_mutex_unlock(&counter_mutex);
    /* loop for callback function */
    traffic_summary[thread_c] = 0;
    pcap_loop(descr[thread_c], -1, counter_callback, (u_char*) thread_c);

exit_thread:
    pthread_mutex_lock(&counter_mutex);
    snprintf(msg, sz, "Exiting thread #%ld", thread_c);
    writeToStoreLog(msg);
    pthread_mutex_unlock(&counter_mutex);

    pthread_exit((void *) 0);
}

void counter_callback(u_char * thrc, const struct pcap_pkthdr *header, const u_char *packet) {
    (void) header, (void) packet;
    void *buf;
    unsigned len;
    long i = (long) thrc;
    traffic_summary[i] += (long) header->len;

    if (traffic_summary[i] >= globals.rules[i].dump_limit) {

        pthread_mutex_lock(&send_msg_mutex);
        TrafficInfo msg = TRAFFIC_INFO__INIT;
        /* fill the message */
        msg.amount = traffic_summary[i];
        msg.desc = globals.rules[i].desc;
        msg.rule = globals.rules[i].filter;
        msg.timestamp = time(NULL);
        msg.ident = globals.unique_id_line;
        msg.source_addr = globals.rules[i].laddress;
        len = traffic_info__get_packed_size(&msg);
        buf = malloc(len);
        traffic_info__pack(&msg, buf);
        /* send the message */
        sendMsg(buf,len);
        free(buf);
        pthread_mutex_unlock(&send_msg_mutex);
        traffic_summary[i] = 0;
    }
}
