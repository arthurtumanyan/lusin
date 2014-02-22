/*
 * File:   lusin_store.h
 * Author: root
 *
 * Created on July 23, 2013, 8:20 PM
 */

#ifndef LUSIN_STORE_H
#define LUSIN_STORE_H

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
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/if_ether.h>
#include <ctype.h>

#ifdef   __cplusplus
extern "C" {
#endif

#define IDENTLINE "LusinStore"
#define CFG_PARAM_LEN 32
#define KB 1024UL
#define MB 1024UL * KB
#define GB 1024UL * MB
#define TB 1024UL * GB
#define FREE(ptr) do{ \
    free((ptr));      \
    (ptr) = NULL;     \
  }while(0)
    FILE * store_log_fd = NULL;
    FILE * pid_fd = NULL;
    bool listen_stop_flag;
    struct passwd *pwd;
    struct group *grp;
    struct stat status;

    uid_t my_uid;
    gid_t my_gid;
    pid_t pid, sid;
    time_t ticks,start_time;

    struct {
        char * configfile;
    } arguments;

    struct {
        char * pidfile;
        char * logfile;
        char * user;
        char * group;
        char * bfile;
        char * listen_host;
#if (LIBCONFIG_VER_MAJOR == 1 && LIBCONFIG_VER_MINOR >= 4) 
        long listen_port;
        long db_port;
#else
        int listen_port;
        int db_port;
#endif
        char * db_host;

        char * db_user;
        char * db_password;
        char * db_name;
        char * tbl_name;
        char * tbl_name_prefix;
        //
        char * tramount_field_name;
        char * timestamp_field_name;
        char * srcip_field_name;
        char * senderip_field_name;
        char * ident_field_name;
        char * rule_field_name;
        char * desc_field_name;
    } globals;


    static const struct option longOpts[] = {
        {
            "pidfile", required_argument, NULL, 'p'
        },
        {
            "logfile", required_argument, NULL, 'l'
        },
        {
            "configfile", required_argument, NULL, 'c'
        },
        {
            "user", required_argument, NULL, 'u'
        },
        {
            "group", required_argument, NULL, 'g'
        },
        {
            "help", no_argument, NULL, 'h'
        },
        {
            NULL, no_argument, NULL, 0
        }
    };

#ifdef   __cplusplus
}
#endif

#endif   /* LUSIN_STORE_H */
