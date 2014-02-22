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
/*
 * 
 */

static bool is_valid_opt(char *opts);
static void print_usage();

static bool is_valid_opt(char *opts) {
    if (opts == NULL)return false;
    if (opts[0] == '-' || opts[0] == ':' || opts[0] == '?')return false;

    return true;
}

int main(int argc, char** argv) {

    char msg[64];
    memset(msg, '\0', 64);

    if (0 != getuid()) {
        printf("Insufficent privileges\n");
        exit(EXIT_FAILURE);
    }

    char * argument = NULL;

    globals.rules_cnt = 0;
    //
    argument = "/var/run/lusin_counter.pid";
    globals.pidfile = xmalloc(sizeof (char) * strlen(argument) + 1);
    memset(globals.pidfile, '\0', strlen(argument) + 1);
    strcpy(globals.pidfile, argument);
    //
    argument = "lusin";
    globals.user = xmalloc(sizeof (char) * strlen(argument) + 1);
    memset(globals.user, '\0', strlen(argument) + 1);
    strcpy(globals.user, argument);
    //
    argument = "lusin";
    globals.group = xmalloc(sizeof (char) * strlen(argument) + 1);
    memset(globals.group, '\0', strlen(argument) + 1);
    strcpy(globals.group, argument);
    //
    argument = "/etc/lusin_counter.conf";
    arguments.configfile = xmalloc(sizeof (char) * strlen(argument) + 1);
    memset(arguments.configfile, '\0', strlen(argument) + 1);
    strcpy(arguments.configfile, argument);
    //
    argument = "/var/log/lusin_counter.log";
    globals.logfile = xmalloc(sizeof (char) * strlen(argument) + 1);
    memset(globals.logfile, '\0', strlen(argument) + 1);
    strcpy(globals.logfile, argument);

    argument = "localhost";
    globals.storage_srv_host = xmalloc(sizeof (char) * strlen(argument) + 1);
    memset(globals.storage_srv_host, '\0', strlen(argument) + 1);
    strcpy(globals.storage_srv_host, argument);

    argument = "QajNazar";
    globals.unique_id_line = xmalloc(sizeof (char) * strlen(argument) + 1);
    memset(globals.unique_id_line, '\0', strlen(argument) + 1);
    strcpy(globals.unique_id_line, argument);

    globals.storage_srv_port = 803;

    int opt = 0;
    int longIndex = 0;
    static const char *optString = "p:l:c:u:g:h?";
    opt = getopt_long(argc, argv, optString, longOpts, &longIndex);

    while (opt != -1) {
        switch (opt) {
            case 'p':
                if (!is_valid_opt(optarg)) {
                    print_usage();
                }
                globals.pidfile = xrealloc(globals.pidfile, (sizeof (char) * strlen(optarg) + 1));
                memset(globals.pidfile, '\0', strlen(optarg) + 1);
                strcpy(globals.pidfile, optarg);

                break;

            case 'l':
                if (!is_valid_opt(optarg)) {
                    print_usage();
                }
                globals.logfile = xrealloc(globals.logfile, (sizeof (char) * strlen(optarg) + 1));
                memset(globals.logfile, '\0', strlen(optarg) + 1);
                strcpy(globals.logfile, optarg);
                break;

            case 'c':
                if (!is_valid_opt(optarg)) {
                    print_usage();
                }
                arguments.configfile = xrealloc(arguments.configfile, (sizeof (char) * strlen(optarg) + 1));
                memset(arguments.configfile, '\0', strlen(optarg) + 1);
                strcpy(arguments.configfile, optarg);
                break;

            case 'u':
                if (!is_valid_opt(optarg)) {
                    print_usage();
                }
                globals.user = xrealloc(globals.user, (sizeof (char) * strlen(optarg) + 1));
                memset(globals.user, '\0', strlen(optarg) + 1);
                strcpy(globals.user, optarg);
                break;
            case 'g':
                globals.group = xrealloc(globals.group, (sizeof (char) * strlen(optarg) + 1));
                memset(globals.group, '\0', strlen(optarg) + 1);
                strcpy(globals.group, optarg);
                break;

            case 'h':
                print_usage();
                break;

            default:
                if (!is_valid_opt(optarg)) {
                    print_usage();
                }
                break;
        }

        opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
    }
    set_sig_handler();
    openCounterLog();
    readConfig(arguments.configfile);
    checkPid();


    if (!(pwd = getpwnam(globals.user))) {
        snprintf(msg, 64, "No such user: %s. Quitting!", globals.user);
        writeToStoreLog(msg);
        exit(EXIT_FAILURE);
    } else my_uid = pwd->pw_uid;

    if (!(grp = getgrnam(globals.group))) {
        snprintf(msg, 64, "No such group: %s. Quitting!", globals.group);
        writeToStoreLog(msg);
        exit(EXIT_FAILURE);
    } else my_gid = grp->gr_gid;

        pid = fork();
    
        if (pid < 0) {
            snprintf(msg, 64, "%s", "Can not fork! [Invalid PID]");
            writeToStoreLog(msg);
            removePid();
            exit(EXIT_FAILURE);
        }
        /* If we got a good PID, then
           we can exit the parent process. */
        if (pid > 0) {
            exit(EXIT_SUCCESS);
        }
        //
        snprintf(msg, 64, "%s", "Forked successfully");
        writeToStoreLog(msg);
        /* Change the file mode mask */
        umask(027);
        /* Create a new SID for the child process */
        sid = setsid();
        if (sid < 0) {
            snprintf(msg, 64, "%s", "Can not create child process");
            writeToStoreLog(msg);
            /* Log the failure */
            removePid();
            exit(EXIT_FAILURE);
        }
        snprintf(msg, 64, "%s", "Daemonizing");
        writeToStoreLog(msg);
    
        /* Change the current working directory */
        if ((chdir("/tmp")) < 0) {
            snprintf(msg, 64, "%s", "Can not change current directory");
            writeToStoreLog(msg);
            /* Log the failure */
            exit(EXIT_FAILURE);
        }
        snprintf(msg, 64, "%s", "Working directory changed to /tmp");
        writeToStoreLog(msg);
    //
    savePid();

    if ((setgid(my_gid)) < 0) {
        snprintf(msg, 64, "ERROR: setgid(%d) failed: %s", my_gid, strerror(errno));
        writeToStoreLog(msg);
        halt();
    }
    snprintf(msg, 64, "Group ID changed to %d", my_gid);
    writeToStoreLog(msg);

    if ((setuid(my_uid)) < 0) {
        snprintf(msg, 64, "ERROR: setuid(%d) failed: %s", my_uid, strerror(errno));
        writeToStoreLog(msg);
        halt();
    }
    snprintf(msg, 64, "User ID changed to %d", my_gid);
    writeToStoreLog(msg);

    pthread_t thread[globals.rules_cnt];
    /* Initialize and set thread detached attribute */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    long t = 0;
    //
    dev = xmalloc(globals.rules_cnt * sizeof (char *));
    for (t = 0; t < globals.rules_cnt; t++) {
        dev[t] = NULL;
    }
    //
    descr = xmalloc(globals.rules_cnt * sizeof (pcap_t *));

    //
    fp = xmalloc(globals.rules_cnt * sizeof (struct bpf_program));
    for (t = 0; t < globals.rules_cnt; t++) {
        fp[t].bf_insns = NULL;
        fp[t].bf_len = 0;
    }
    //
    maskp = xmalloc(globals.rules_cnt * sizeof (struct bpf_u_int32 *));
    netp = xmalloc(globals.rules_cnt * sizeof (struct bpf_u_int32 *));

    for (t = 0; t < globals.rules_cnt; t++) {
        if (!globals.rules[t].enabled)continue;
        snprintf(msg, 64, "Creating thread #%ld for rule %d", t, (int)globals.rules[t].id);
        writeToStoreLog(msg);
        rc = pthread_create(&thread[t], &attr, process_counter, (void *) t);
        if (rc) {
            snprintf(msg, 64, "Cannot create a thread: %s", strerror(errno));
            writeToStoreLog(msg);
            halt();
        }
    }

    /* Free attribute and wait for the other threads */
    pthread_attr_destroy(&attr);
    for (t = 0; t < globals.rules_cnt; t++) {
        rc = pthread_join(thread[t], &t_status);
        if (rc) {
            snprintf(msg, 64, "Cannot join the thread #%ld: %s", t, strerror(errno));
            writeToStoreLog(msg);
            halt();
        }
        snprintf(msg, 64, "Thread #%ld joined successfully", t);
        writeToStoreLog(msg);
    }
    halt();
    return 0;
}

static void print_usage() {

    printf("%s\t%30s", "-p |--pidfile", "pidfile\n");
    printf("%s\t%30s", "-l |--logfile", "logfile\n");
    printf("%s\t%33s", "-c |--configfile", "configuration file\n");
    printf("%s\t%35s", "-u |--user", "working user\n");
    printf("%s\t%36s", "-g |--group", "working group\n");
    printf("%s\t%32s", "-h |--help", "this help\n");
    exit(EXIT_SUCCESS);
}

void halt() {

    char msg[64];
    memset(msg, '\0', 64);

    snprintf(msg, 64, "Breaking counter loops");
    writeToStoreLog(msg);
    int t;
    for (t = 0; t < globals.rules_cnt; t++) {
        if(NULL != descr[t]){
            pcap_breakloop(descr[t]);
        }
        sleep(1);
    }
    //
    snprintf(msg, 64, "Closing pid file");
    writeToStoreLog(msg);
    removePid();

    memset(msg, '\0', 64);
    snprintf(msg, 64, "Shutting down");
    writeToStoreLog(msg);
    closeCounterLog();

    if (dev) {
        FREE(dev);
    }

    if (descr) {
        FREE(descr);
    }

    if (fp) {
        FREE(fp);
    }

    if (maskp) {
        FREE(maskp);
    }

    if (netp) {
        FREE(netp);
    }

    if (globals.pidfile) {
        FREE(globals.pidfile);
    }

    if (globals.logfile) {
        FREE(globals.logfile);
    }

    if (arguments.configfile) {
        FREE(arguments.configfile);
    }

    if (globals.user) {
        FREE(globals.user);
    }

    if (globals.group) {
        FREE(globals.group);
    }

    if (globals.logfile) {
        FREE(globals.logfile);
    }
    exit(EXIT_SUCCESS);
}

void savePid() {
    int sz = sizeof (globals.pidfile) + 64;
    char msg[sz];

    if ((pid_fd = fopen(globals.pidfile, "w")) == NULL) {
        snprintf(msg, sz, "Cannot create PID file '%s'.Exiting nicely! - %s", globals.pidfile, strerror(errno));
        writeToStoreLog(msg);
        exit(EXIT_FAILURE);
    } else {
        snprintf(msg, sz, "Process ID stored in: '%s',%d", globals.pidfile, errno);
        writeToStoreLog(msg);
    }
    fprintf(pid_fd, "%d", getpid());

    if (pid_fd)fclose(pid_fd);
}

/**
 *
 * @return
 */
int checkPid() {
    pid_t S_PID;
    if ((pid_fd = fopen(globals.pidfile, "r")) != NULL) {
        (void) fscanf(pid_fd, "%d", &S_PID);
        if (pid_fd)fclose(pid_fd);

        if (kill(S_PID, 18) == 0) {
            printf("Can be only one running daemon with the same settings!Quitting...\n");
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}

void removePid() {
    int sz = sizeof (globals.pidfile) + 64;
    char msg[sz];
    if (0 != unlink(globals.pidfile)) {
        snprintf(msg, sz, "Cannot unlink file '%s',%s", globals.pidfile, strerror(errno));
        writeToStoreLog(msg);
    } else {
        snprintf(msg, sz, "Pid file '%s' removed", globals.pidfile);
        writeToStoreLog(msg);
    }
}

