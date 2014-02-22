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

extern void * xmalloc(size_t size);
extern void * xrealloc(void *ptr, size_t size);
extern void * xcalloc(size_t nmemb, size_t size);

extern FILE * openCounterLog();
extern void closeCounterLog();
extern void writeToStoreLog(char *log_string);
extern void write_syslog(char *msg);

extern void halt();
extern void savePid();
extern int checkPid();
extern void removePid();

extern void readConfig(char *cfile);

extern void *process_counter(void *);
extern void set_sig_handler();

extern char * getIpByIf(const char *interface);
extern void sendMsg(void *msg, int sz);
extern void counter_callback(u_char *, const struct pcap_pkthdr *header, const u_char *packet);