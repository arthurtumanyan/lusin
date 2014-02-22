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
#include <libconfig.h>

void readConfig(char *cfile) {

    config_t cfg, *cf;
    const config_setting_t *rules = NULL;
    int sz = 128, count = 0;
    char msg[sz];

    const char * pidfile = NULL;
    const char * logfile = NULL;
    const char * user = NULL;
    const char * group = NULL;
    const char * storage_srv_host = NULL;
    const char * unique_id_line = NULL;
    const char * desc = NULL;
    const char * filter = NULL;
    const char * device = NULL;
    int dump_limit = 0;

    int i = 0;
    cf = &cfg;
    config_init(cf);

    if (CONFIG_FALSE == config_read_file(cf, cfile)) {
        printf("Something wrong in %s, line #%d - %s. Exiting...\n",
                cfile,
                config_error_line(cf) - 1,
                config_error_text(cf));
        config_destroy(cf);

        exit(EXIT_FAILURE);
    } else {
        snprintf(msg, sz, "Reading configuration file '%s'", cfile);
        writeToStoreLog(msg);
    }

    /*
     * 
     */
    pidfile = xmalloc(sizeof (char) * CFG_PARAM_LEN);
    if (!config_lookup_string(cf, "pidfile", &pidfile)) {
        snprintf(msg, sz, "%s", "Using default value of 'pidfile'");
        writeToStoreLog(msg);
    } else {
        int pid_sz = strlen(pidfile) + 1;
        globals.pidfile = xrealloc(globals.pidfile, (sizeof (char) * pid_sz));
        memset(globals.pidfile, '\0', pid_sz);
        strcpy(globals.pidfile, pidfile);
        globals.pidfile[pid_sz - 1] = '\0';
        pidfile = NULL;
    }

    /*
     * 
     */
    globals.logfile = xmalloc(sizeof (char) * CFG_PARAM_LEN);
    if (!config_lookup_string(cf, "logfile", &logfile)) {
        snprintf(msg, sz, "%s", "Using default value of 'logfile'");
        writeToStoreLog(msg);
    } else {
        int log_sz = strlen(logfile) + 1;
        globals.logfile = xrealloc(globals.logfile, (sizeof (char) * log_sz));
        memset(globals.logfile, '\0', strlen(logfile) + 1);
        strcpy(globals.logfile, logfile);
        globals.logfile[log_sz - 1] = '\0';
        logfile = NULL;

        closeCounterLog();
        openCounterLog();
    }

    /*
     * 
     */
    user = xmalloc(sizeof (char) * CFG_PARAM_LEN);
    if (!config_lookup_string(cf, "user", &user)) {
        snprintf(msg, sz, "%s", "Using default value of 'user'");
        writeToStoreLog(msg);
    } else {
        int user_sz = strlen(user) + 1;
        globals.user = xrealloc(globals.user, (sizeof (char) * user_sz));
        memset(globals.user, '\0', user_sz);
        strcpy(globals.user, user);
        globals.user[user_sz - 1] = '\0';
        user = NULL;
    }
    //
    group = xmalloc(sizeof (char) * CFG_PARAM_LEN);
    if (!config_lookup_string(cf, "group", &group)) {
        snprintf(msg, sz, "%s", "Using default value of 'group'");
        writeToStoreLog(msg);
    } else {
        int group_sz = strlen(group) + 1;
        globals.group = xrealloc(globals.group, (sizeof (char) * group_sz));
        memset(globals.group, '\0', group_sz);
        strcpy(globals.group, group);
        globals.group[group_sz - 1] = '\0';
        group = NULL;
    }

    /*
     * 
     */
    storage_srv_host = xmalloc(sizeof (char) * CFG_PARAM_LEN);
    if (!config_lookup_string(cf, "storage-server-host", &storage_srv_host)) {
        snprintf(msg, sz, "%s", "Using default value of 'storage-server-host'");
        writeToStoreLog(msg);
    } else {
        int storage_srv_host_sz = strlen(storage_srv_host) + 1;
        globals.storage_srv_host = xrealloc(globals.storage_srv_host, (sizeof (char) * storage_srv_host_sz));
        memset(globals.storage_srv_host, '\0', storage_srv_host_sz);
        strcpy(globals.storage_srv_host, storage_srv_host);
        globals.storage_srv_host[storage_srv_host_sz - 1] = '\0';
        storage_srv_host = NULL;
    }
    //
        unique_id_line  = xmalloc(sizeof (char) * CFG_PARAM_LEN);
    if (!config_lookup_string(cf, "unique-id-line", &unique_id_line )) {
        snprintf(msg, sz, "%s", "Using default value of 'unique-id-line'");
        writeToStoreLog(msg);
    } else {
        int unique_id_line_sz = strlen(unique_id_line) + 1;
        globals.unique_id_line  = xrealloc(globals.unique_id_line, (sizeof (char) * unique_id_line_sz));
        memset(globals.unique_id_line, '\0', unique_id_line_sz);
        strcpy(globals.unique_id_line, unique_id_line);
        globals.unique_id_line[unique_id_line_sz - 1] = '\0';
        unique_id_line = NULL;
    }
    //
    if (!config_lookup_int(cf, "storage-server-port", &globals.storage_srv_port)) {
        snprintf(msg, sz, "%s", "Using default value of 'storage-server-port'");
        writeToStoreLog(msg);
    }
    //
    rules = config_lookup(cf, "rules");
    if (NULL == rules) {
        snprintf(msg, sz, "Undefined section '%s'. Exiting.", "rules");
        writeToStoreLog(msg);
        exit(EXIT_FAILURE);

    }
    count = config_setting_length(rules);
    if (count > BPF_MAX_COUNT)count = BPF_MAX_COUNT;
    globals.rules_cnt = count;
    snprintf(msg, sz, "Rules count restricted to %d", BPF_MAX_COUNT);
    writeToStoreLog(msg);

    for (i = 0; i < count; ++i) {
        config_setting_t *rule = config_setting_get_elem(rules, i);

        ////////////////////////////////////////////////////////////////////////////////
        if (!config_setting_lookup_int(rule, "id", &globals.rules[i].id)) {
            snprintf(msg, sz, "Can not find 'id' for rules");
            writeToStoreLog(msg);
            exit(EXIT_FAILURE);
        }
        //
        if (!config_setting_lookup_bool(rule, "enabled", &globals.rules[i].enabled)) {
            snprintf(msg, sz, "Can not find 'enabled' for rules");
            writeToStoreLog(msg);
            exit(EXIT_FAILURE);
        }
        //
        if (!config_setting_lookup_string(rule, "desc", &desc)) {
            snprintf(msg, sz, "Can not find description for rule: id = %d", (int)globals.rules[i].id);
            writeToStoreLog(msg);
            exit(EXIT_FAILURE);
        } else {
            if (0 == strcasecmp(desc, "")) {
                snprintf(msg, sz, "Empty description for rule: id = %d", (int)globals.rules[i].id);
                writeToStoreLog(msg);
            }
            globals.rules[i].desc = xmalloc(sizeof (char) * (strlen(desc) + 1));
            memset(globals.rules[i].desc, '\0', strlen(desc) + 1);
            strcpy(globals.rules[i].desc, desc);
            globals.rules[i].desc[strlen(desc)] = '\0';
        }
        //
        if (!config_setting_lookup_string(rule, "filter", &filter)) {
            snprintf(msg, sz, "Can not find filter expression for rule: id = %d", (int)globals.rules[i].id);
            writeToStoreLog(msg);
            exit(EXIT_FAILURE);
        } else {
            if (0 == strcasecmp(filter, "")) {
                snprintf(msg, sz, "Empty filter expression for rule: id = %d", (int)globals.rules[i].id);
                writeToStoreLog(msg);
            }
            globals.rules[i].filter = xmalloc(sizeof (char) * (strlen(filter) + 1));
            memset(globals.rules[i].filter, '\0', strlen(filter) + 1);
            strcpy(globals.rules[i].filter, filter);
            globals.rules[i].filter[strlen(filter)] = '\0';
        }
        //
        if (!config_setting_lookup_string(rule, "device", &device)) {
            snprintf(msg, sz, "Can not find device name for rule: id = %d", (int)globals.rules[i].id);
            writeToStoreLog(msg);
            exit(EXIT_FAILURE);
        } else {
            if (0 == strcasecmp(device, "")) {
                snprintf(msg, sz, "Empty device name for rule: id = %d", (int)globals.rules[i].id);
                writeToStoreLog(msg);
            }
            globals.rules[i].device = xmalloc(sizeof (char) * (strlen(device) + 1));
            memset(globals.rules[i].device, '\0', strlen(device) + 1);
            strcpy(globals.rules[i].device, device);
            globals.rules[i].device[strlen(device)] = '\0';
        }
        //
        if (!config_setting_lookup_int(rule, "dump-limit", &dump_limit)) {
            snprintf(msg, sz, "Can not find 'dump-limit' for rules");
            writeToStoreLog(msg);
            exit(EXIT_FAILURE);
        } else {
            globals.rules[i].dump_limit = dump_limit * MB;
        }
    
        globals.rules[i].laddress = getIpByIf(globals.rules[i].device);
    }

    /*
     * end of readConfig
     */
    config_destroy(cf);
}


