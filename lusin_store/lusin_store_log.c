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
#include <syslog.h>

void write_syslog(char * msg) {
    openlog(IDENTLINE, LOG_PID, LOG_USER);
    syslog(LOG_INFO, "%s", msg);
    closelog();
}

FILE * openStoreLog() {
    if (0 == strcasecmp(globals.logfile, "")) {
        return NULL;
    }

    //
    if (NULL == (store_log_fd = fopen(globals.logfile, "a+"))) {
        printf("Cannot create log file '%s' - %s\n", globals.logfile, strerror(errno));
        exit(EXIT_FAILURE);
    }

    return store_log_fd;
}

void closeStoreLog() {
    if (0 != strcasecmp(globals.logfile, "")) {
        if (NULL != store_log_fd) {
            fclose(store_log_fd);

            store_log_fd = NULL;
        }
    }
}

void writeToStoreLog(char * log_string) {
    ticks = time(NULL);

    char d_time[24];

    snprintf(d_time, 24, "%.24s", ctime(&ticks));

    if (NULL != store_log_fd) {
        fprintf(store_log_fd, "[%s][pid %d] %s\n", d_time, getpid(), log_string);
        fflush(store_log_fd);
    } else {
        write_syslog(log_string);
    }
}

void addToBackupFile(char * query_string) {
    FILE *hdl = NULL;
    if (0 == strcasecmp(globals.bfile, "")) {
        return;
    }
    if (NULL == (hdl = fopen(globals.bfile, "a+"))) {
        printf("Cannot access log file '%s' - %s\n", globals.bfile, strerror(errno));
    }
    fprintf(hdl, "%s\n", query_string);
    fflush(hdl);
    fclose(hdl);
}