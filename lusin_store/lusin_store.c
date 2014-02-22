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

#include "lusin_store.h"
#include "lusin_store_prototypes.h"

/*
 *
 */
static bool is_valid_opt(char * opts);

static void print_usage();

static bool is_valid_opt(char * opts)
{
    if (opts == NULL)
    {
        return false;
    }

    if ((opts[0] == '-') || (opts[0] == ':') || (opts[0] == '?'))
    {
        return false;
    }

    return true;
}

int main(int argc,
         char ** argv)
{
    char msg[64];
    start_time = time(NULL);
    memset(msg, '\0', 64);

    if (0 != getuid())
    {
        printf("Insufficent privileges\n");
        exit(EXIT_FAILURE);
    }

    char * argument = NULL;
    listen_stop_flag = false;
    //
    argument = "/var/run/lusin_store.pid";
    globals.pidfile = xmalloc(sizeof (char) * strlen(argument) + 1);

    memset(globals.pidfile, '\0', strlen(argument) + 1);
    strcpy(globals.pidfile, argument);
    //
    argument = "ls_backup.sql";
    globals.bfile = xmalloc(sizeof (char) * strlen(argument) + 1);

    memset(globals.bfile, '\0', strlen(argument) + 1);
    strcpy(globals.bfile, argument);
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
    argument = "/etc/lusin_store.conf";
    arguments.configfile = xmalloc(sizeof (char) * strlen(argument) + 1);

    memset(arguments.configfile, '\0', strlen(argument) + 1);
    strcpy(arguments.configfile, argument);

    //
    argument = "/var/log/lusin_store.log";
    globals.logfile = xmalloc(sizeof (char) * strlen(argument) + 1);

    memset(globals.logfile, '\0', strlen(argument) + 1);
    strcpy(globals.logfile, argument);

    argument = "localhost";
    globals.listen_host = xmalloc(sizeof (char) * strlen(argument) + 1);

    memset(globals.listen_host, '\0', strlen(argument) + 1);
    strcpy(globals.listen_host, argument);

    globals.listen_port = 803;
    argument = "localhost";
    globals.db_host = xmalloc(sizeof (char) * strlen(argument) + 1);

    memset(globals.db_host, '\0', strlen(argument) + 1);
    strcpy(globals.db_host, argument);

    globals.db_port = 3306;
    argument = "lusin";
    globals.db_user = xmalloc(sizeof (char) * strlen(argument) + 1);

    memset(globals.db_user, '\0', strlen(argument) + 1);
    strcpy(globals.db_user, argument);

    argument = "lusin";
    globals.db_password = xmalloc(sizeof (char) * strlen(argument) + 1);

    memset(globals.db_password, '\0', strlen(argument) + 1);
    strcpy(globals.db_password, argument);

    argument = "lusin";
    globals.db_name = xmalloc(sizeof (char) * strlen(argument) + 1);

    memset(globals.db_name, '\0', strlen(argument) + 1);
    strcpy(globals.db_name, argument);

    argument = "lusin_tbl";
    globals.tbl_name = xmalloc(sizeof (char) * strlen(argument) + 1);

    memset(globals.tbl_name, '\0', strlen(argument) + 1);
    strcpy(globals.tbl_name, argument);

    argument = "local";
    globals.tbl_name_prefix = xmalloc(sizeof (char) * strlen(argument) + 1);

    memset(globals.tbl_name_prefix, '\0', strlen(argument) + 1);
    strcpy(globals.tbl_name_prefix, argument);

    argument = "tr_amount";
    globals.tramount_field_name = xmalloc(sizeof (char) * strlen(argument) + 1);

    memset(globals.tramount_field_name, '\0', strlen(argument) + 1);
    strcpy(globals.tramount_field_name, argument);

    argument = "timestamp";
    globals.timestamp_field_name = xmalloc(sizeof (char) * strlen(argument) + 1);

    memset(globals.timestamp_field_name, '\0', strlen(argument) + 1);
    strcpy(globals.timestamp_field_name, argument);

    argument = "srcip";
    globals.srcip_field_name = xmalloc(sizeof (char) * strlen(argument) + 1);

    memset(globals.srcip_field_name, '\0', strlen(argument) + 1);
    strcpy(globals.srcip_field_name, argument);

    argument = "ident";
    globals.ident_field_name = xmalloc(sizeof (char) * strlen(argument) + 1);

    memset(globals.ident_field_name, '\0', strlen(argument) + 1);
    strcpy(globals.ident_field_name, argument);

    argument = "rules";
    globals.rule_field_name = xmalloc(sizeof (char) * strlen(argument) + 1);

    memset(globals.rule_field_name, '\0', strlen(argument) + 1);
    strcpy(globals.rule_field_name, argument);

    argument = "desc";
    globals.desc_field_name = xmalloc(sizeof (char) * strlen(argument) + 1);

    memset(globals.desc_field_name, '\0', strlen(argument) + 1);
    strcpy(globals.desc_field_name, argument);

    int opt = 0;
    int longIndex = 0;
    static const char * optString = "p:l:c:u:g:h?";

    opt = getopt_long(argc, argv, optString, longOpts, &longIndex);

    while (opt != -1)
    {
        switch (opt)
        {
        case 'p':
            if (!is_valid_opt(optarg))
            {
                print_usage();
            }

            globals.pidfile = xrealloc(globals.pidfile, (sizeof (char) * strlen(optarg) + 1));

            memset(globals.pidfile, '\0', strlen(optarg) + 1);
            strcpy(globals.pidfile, optarg);

            break;

        case 'l':
            if (!is_valid_opt(optarg))
            {
                print_usage();
            }

            globals.logfile = xrealloc(globals.logfile, (sizeof (char) * strlen(optarg) + 1));

            memset(globals.logfile, '\0', strlen(optarg) + 1);
            strcpy(globals.logfile, optarg);

            break;

        case 'c':
            if (!is_valid_opt(optarg))
            {
                print_usage();
            }

            arguments.configfile = xrealloc(arguments.configfile, (sizeof (char) * strlen(optarg) + 1));

            memset(arguments.configfile, '\0', strlen(optarg) + 1);
            strcpy(arguments.configfile, optarg);

            break;

        case 'u':
            if (!is_valid_opt(optarg))
            {
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
            if (!is_valid_opt(optarg))
            {
                print_usage();
            }

            break;
        }

        opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
    }

    set_sig_handler();
    openStoreLog();
    readConfig(arguments.configfile);
    checkPid();

    if (!(pwd = getpwnam(globals.user)))
    {
        snprintf(msg, 64, "No such user: %s. Quitting!", globals.user);
        writeToStoreLog(msg);
        exit(EXIT_FAILURE);
    }
    else
    {
        my_uid = pwd -> pw_uid;
    }

    if (!(grp = getgrnam(globals.group)))
    {
        snprintf(msg, 64, "No such group: %s. Quitting!", globals.group);
        writeToStoreLog(msg);
        exit(EXIT_FAILURE);
    }
    else
    {
        my_gid = grp -> gr_gid;
    }

    pid = fork();

    if (pid < 0)
    {
        snprintf(msg, 64, "%s", "Can not fork! [Invalid PID]");
        writeToStoreLog(msg);
        removePid();
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then
    we can exit the parent process. */
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }
    //
    snprintf(msg, 64, "%s", "Forked successfully");
    writeToStoreLog(msg);
    /* Change the file mode mask */
    umask(027);
    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0)
    {
        snprintf(msg, 64, "%s", "Can not create child process");
        writeToStoreLog(msg);
        /* Log the failure */
        removePid();
        exit(EXIT_FAILURE);
    }
    snprintf(msg, 64, "%s", "Daemonizing");
    writeToStoreLog(msg);

    // /* Change the current working directory */
    if ((chdir("/tmp")) < 0)
    {
        snprintf(msg, 64, "%s", "Can not change current directory");
        writeToStoreLog(msg);
        /* Log the failure */
        exit(EXIT_FAILURE);
    }
    snprintf(msg, 64, "%s", "Working directory changed to /tmp");
    writeToStoreLog(msg);

    savePid();

    if ((setgid(my_gid)) < 0)
    {
        snprintf(msg, 64, "ERROR: setgid(%d) failed: %s", my_gid, strerror(errno));
        writeToStoreLog(msg);
        halt();
    }

    snprintf(msg, 64, "Group ID changed to %d", my_gid);
    writeToStoreLog(msg);

    if ((setuid(my_uid)) < 0)
    {
        snprintf(msg, 64, "ERROR: setuid(%d) failed: %s", my_uid, strerror(errno));
        writeToStoreLog(msg);
        halt();
    }

    snprintf(msg, 64, "User ID changed to %d", my_gid);
    writeToStoreLog(msg);
    //
    CONNECT_TO_DB();
    do_listen();
    halt();

    return 0;
}

static void print_usage()
{
    printf("%s\t%30s", "-p |--pidfile", "pidfile\n");
    printf("%s\t%30s", "-l |--logfile", "logfile\n");
    printf("%s\t%33s", "-c |--configfile", "configuration file\n");
    printf("%s\t%35s", "-u |--user", "working user\n");
    printf("%s\t%36s", "-g |--group", "working group\n");
    printf("%s\t%32s", "-h |--help", "this help\n");
    exit(EXIT_SUCCESS);
}

void halt()
{
    char msg[64];
    memset(msg, '\0', 64);
    //
    listen_stop_flag = true;
    CLOSE_DB();
    snprintf(msg, 64, "Closing pid file");
    writeToStoreLog(msg);
    removePid();
    memset(msg, '\0', 64);
    snprintf(msg, 64, "Shutting down");
    writeToStoreLog(msg);
    closeStoreLog();

    if (globals.pidfile)
    {
        FREE(globals.pidfile);
    }

    if (globals.logfile)
    {
        FREE(globals.logfile);
    }

    if (arguments.configfile)
    {
        FREE(arguments.configfile);
    }

    if (globals.user)
    {
        FREE(globals.user);
    }

    if (globals.group)
    {
        FREE(globals.group);
    }

    if (globals.logfile)
    {
        FREE(globals.logfile);
    }

    if (globals.listen_host)
    {
        FREE(globals.listen_host);
    }

    if (globals.db_host)
    {
        FREE(globals.db_host);
    }

    if (globals.db_name)
    {
        FREE(globals.db_name);
    }

    if (globals.tbl_name)
    {
        FREE(globals.tbl_name);
    }

    if (globals.db_password)
    {
        FREE(globals.db_password);
    }

    if (globals.db_user)
    {
        FREE(globals.db_user);
    }

    if (globals.desc_field_name)
    {
        FREE(globals.desc_field_name);
    }

    if (globals.ident_field_name)
    {
        FREE(globals.ident_field_name);
    }

    if (globals.rule_field_name)
    {
        FREE(globals.rule_field_name);
    }

    if (globals.srcip_field_name)
    {
        FREE(globals.srcip_field_name);
    }

    if (globals.timestamp_field_name)
    {
        FREE(globals.timestamp_field_name);
    }

    exit(EXIT_SUCCESS);
}

void savePid()
{
    int sz = sizeof (globals.pidfile) + 64;
    char msg[sz];

    if ((pid_fd = fopen(globals.pidfile, "w")) == NULL)
    {
        snprintf(msg, sz, "Cannot create PID file '%s'.Exiting nicely! - %s", globals.pidfile, strerror(errno));
        writeToStoreLog(msg);
        exit(EXIT_FAILURE);
    }
    else
    {
        snprintf(msg, sz, "Process ID stored in: '%s',%d", globals.pidfile, errno);
        writeToStoreLog(msg);
    }

    fprintf(pid_fd, "%d", getpid());

    if (pid_fd)
    {
        fclose(pid_fd);
    }
}

/*
 *
 * @return
 */
int checkPid()
{
    pid_t S_PID;

    if ((pid_fd = fopen(globals.pidfile, "r")) != NULL)
    {
        (void) fscanf(pid_fd, "%d", &S_PID);

        if (pid_fd)
        {
            fclose(pid_fd);
        }

        if (kill(S_PID, 18) == 0)
        {
            printf("Can be only one running daemon with the same settings!Quitting...\n");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

/*
 *
 */
void removePid()
{
    int sz = sizeof (globals.pidfile) + 64;
    char msg[sz];

    if (0 != unlink(globals.pidfile))
    {
        snprintf(msg, sz, "Cannot unlink file '%s',%s", globals.pidfile, strerror(errno));
        writeToStoreLog(msg);
    }
    else
    {
        snprintf(msg, sz, "Pid file '%s' removed", globals.pidfile);
        writeToStoreLog(msg);
    }
}
