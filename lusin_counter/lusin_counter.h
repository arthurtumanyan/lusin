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
#ifndef LUSIN_COUNTER_H
#define	LUSIN_COUNTER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <error.h>
#include <getopt.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <pcap.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netinet/if_ether.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <net/if.h>


#ifdef	__cplusplus
extern "C" {
#endif

#define IDENTLINE "LusinCounter"
#define CFG_PARAM_LEN 32
#define KB 1024UL
#define MB 1024UL * KB
#define GB 1024UL * MB
#define TB 1024UL * GB

#define BPF_MAX_COUNT 255
#define FREE(ptr) do{ \
    free((ptr));      \
    (ptr) = NULL;     \
  }while(0)


    char **dev;
    pcap_t **descr;
    struct bpf_program *fp;
    bpf_u_int32 *maskp;
    bpf_u_int32 *netp;

    pthread_mutex_t counter_mutex, send_msg_mutex;
    pthread_attr_t attr;
    int rc;
    char *iface;
    void *t_status;

    FILE * counter_log_fd = NULL;
    FILE * pid_fd = NULL;

    struct passwd *pwd;
    struct group *grp;
    struct stat status;
    uid_t my_uid;
    gid_t my_gid;
    pid_t pid, sid;

    time_t ticks;
#if (LIBCONFIG_VER_MAJOR == 1 && LIBCONFIG_VER_MINOR >= 4) 
    char fmt[] = "%ld";
#else
    char fmt[] = "%d";
#endif

    struct {
        char *configfile;
    } arguments;

    struct {
        char *pidfile;
        char *logfile;
        char *user;
        char *group;
        char *storage_srv_host;
        char *unique_id_line;
#if (LIBCONFIG_VER_MAJOR == 1 && LIBCONFIG_VER_MINOR >= 4) 
        long storage_srv_port;
#else
        int storage_srv_port;
#endif
        int rules_cnt;

        struct {
#if (LIBCONFIG_VER_MAJOR == 1 && LIBCONFIG_VER_MINOR >= 4)             
            long id;
            long dump_limit;
#else
            int id;
            int dump_limit;
#endif
            int enabled;
            char *device;
            char *desc;
            char *filter;
            char *laddress;
        } rules[BPF_MAX_COUNT];
    } globals;

    static const struct option longOpts[] = {
        { "pidfile", required_argument, NULL, 'p'},
        { "logfile", required_argument, NULL, 'l'},
        { "configfile", required_argument, NULL, 'c'},
        { "user", required_argument, NULL, 'u'},
        { "group", required_argument, NULL, 'g'},
        { "help", no_argument, NULL, 'h'},
        { NULL, no_argument, NULL, 0}
    };

#ifdef	__cplusplus
}
#endif

#endif	/* LUSIN_COUNTER_H */

