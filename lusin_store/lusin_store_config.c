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
#include <libconfig.h>

void readConfig(char * cfile)
{
    config_t cfg, *cf;
    const config_setting_t * rules = NULL;
    int sz = 128,
            count = 0;
    char msg[sz];
    const char * pidfile = NULL;
    const char * logfile = NULL;
    const char * bfile = NULL;
    const char * user = NULL;
    const char * group = NULL;
    const char * listen_host = NULL;
    long listen_port;
    const char * db_host = NULL;
    long * db_port;
    const char * db_user = NULL;
    const char * db_password = NULL;
    const char * db_name = NULL;
    const char * tbl_name = NULL;
    const char * tbl_name_prefix = NULL;
    const char * timestamp_field_name = NULL;
    const char * srcip_field_name = NULL;
    const char * senderip_field_name = NULL;
    const char * ident_field_name = NULL;
    const char * rule_field_name = NULL;
    const char * desc_field_name = NULL;
    const char * tramount_field_name = NULL;
    int i = 0;

    cf = &cfg;

    config_init(cf);

    if (CONFIG_FALSE == config_read_file(cf, cfile))
    {
        printf("Something wrong in %s, line #%d - %s. Exiting...\n", cfile, config_error_line(cf) - 1,
               config_error_text(cf));
        config_destroy(cf);
        exit(EXIT_FAILURE);
    }
    else
    {
        snprintf(msg, sz, "Reading configuration file '%s'", cfile);
        writeToStoreLog(msg);
    }

    /*
     *
     */
    pidfile = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "pidfile", &pidfile))
    {
        snprintf(msg, sz, "%s", "Using default value of 'pidfile'");
        writeToStoreLog(msg);
    }
    else
    {
        int pid_sz = strlen(pidfile) + 1;

        globals.pidfile = xrealloc(globals.pidfile, (sizeof (char) * pid_sz));

        memset(globals.pidfile, '\0', pid_sz);
        strcpy(globals.pidfile, pidfile);

        globals.pidfile[pid_sz - 1] = '\0';
        pidfile = NULL;
    }
    /*
     
     */
    bfile = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "backup-sql-file", &bfile))
    {
        snprintf(msg, sz, "%s", "Using default value of 'backup-sql-file'");
        writeToStoreLog(msg);
    }
    else
    {
        int bfile_sz = strlen(bfile) + 1;

        globals.bfile = xrealloc(globals.bfile, (sizeof (char) * bfile_sz));

        memset(globals.bfile, '\0', bfile_sz);
        strcpy(globals.bfile, bfile);

        globals.bfile[bfile_sz - 1] = '\0';
        bfile = NULL;
    }

    /*
     *
     */
    globals.logfile = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "logfile", &logfile))
    {
        snprintf(msg, sz, "%s", "Using default value of 'logfile'");
        writeToStoreLog(msg);
    }
    else
    {
        int log_sz = strlen(logfile) + 1;

        globals.logfile = xrealloc(globals.logfile, (sizeof (char) * log_sz));

        memset(globals.logfile, '\0', strlen(logfile) + 1);
        strcpy(globals.logfile, logfile);

        globals.logfile[log_sz - 1] = '\0';
        logfile = NULL;

        closeStoreLog();
        openStoreLog();
    }

    /*
     *
     */
    user = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "user", &user))
    {
        snprintf(msg, sz, "%s", "Using default value of 'user'");
        writeToStoreLog(msg);
    }
    else
    {
        int user_sz = strlen(user) + 1;

        globals.user = xrealloc(globals.user, (sizeof (char) * user_sz));

        memset(globals.user, '\0', user_sz);
        strcpy(globals.user, user);

        globals.user[user_sz - 1] = '\0';
        user = NULL;
    }

    //
    group = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "group", &group))
    {
        snprintf(msg, sz, "%s", "Using default value of 'group'");
        writeToStoreLog(msg);
    }
    else
    {
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
    listen_host = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "listen-host", &listen_host))
    {
        snprintf(msg, sz, "%s", "Using default value of 'listen-host'");
        writeToStoreLog(msg);
    }
    else
    {
        int listen_host_sz = strlen(listen_host) + 1;

        globals.listen_host = xrealloc(globals.listen_host, (sizeof (char) * listen_host_sz));

        memset(globals.listen_host, '\0', listen_host_sz);
        strcpy(globals.listen_host, listen_host);

        globals.listen_host[listen_host_sz - 1] = '\0';
        listen_host = NULL;
    }

    //
    if (!config_lookup_int(cf, "listen-port", &globals.listen_port))
    {
        snprintf(msg, sz, "%s", "Using default value of 'listen-port'");
        writeToStoreLog(msg);
    }

    //
    db_host = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "db-host", &db_host))
    {
        snprintf(msg, sz, "%s", "Using default value of 'db-host'");
        writeToStoreLog(msg);
    }
    else
    {
        int db_host_sz = strlen(db_host) + 1;

        globals.db_host = xrealloc(globals.db_host, (sizeof (char) * db_host_sz));

        memset(globals.db_host, '\0', db_host_sz);
        strcpy(globals.db_host, db_host);

        globals.db_host[db_host_sz - 1] = '\0';
        db_host = NULL;
    }

    //
    if (!config_lookup_int(cf, "db-port", &globals.db_port))
    {
        snprintf(msg, sz, "%s", "Using default value of 'db-port'");
        writeToStoreLog(msg);
    }

    //
    db_user = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "db-user", &db_user))
    {
        snprintf(msg, sz, "%s", "Using default value of 'db-user'");
        writeToStoreLog(msg);
    }
    else
    {
        int db_user_sz = strlen(db_user) + 1;

        globals.db_user = xrealloc(globals.db_user, (sizeof (char) * db_user_sz));

        memset(globals.db_user, '\0', db_user_sz);
        strcpy(globals.db_user, db_user);

        globals.db_user[db_user_sz - 1] = '\0';
        db_user = NULL;
    }

    //
    db_password = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "db-password", &db_password))
    {
        snprintf(msg, sz, "%s", "Using default value of 'db-password'");
        writeToStoreLog(msg);
    }
    else
    {
        int db_password_sz = strlen(db_password) + 1;

        globals.db_password = xrealloc(globals.db_password, (sizeof (char) * db_password_sz));

        memset(globals.db_password, '\0', db_password_sz);
        strcpy(globals.db_password, db_password);

        globals.db_password[db_password_sz - 1] = '\0';
        db_password = NULL;
    }

    //
    db_name = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "db-name", &db_name))
    {
        snprintf(msg, sz, "%s", "Using default value of 'db-name'");
        writeToStoreLog(msg);
    }
    else
    {
        int db_name_sz = strlen(db_name) + 1;

        globals.db_name = xrealloc(globals.db_name, (sizeof (char) * db_name_sz));

        memset(globals.db_name, '\0', db_name_sz);
        strcpy(globals.db_name, db_name);

        globals.db_name[db_name_sz - 1] = '\0';
        db_name = NULL;
    }

    //
    tbl_name = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "table-name", &tbl_name))
    {
        snprintf(msg, sz, "%s", "Using default value of 'table-name'");
        writeToStoreLog(msg);
    }
    else
    {
        int tbl_name_sz = strlen(tbl_name) + 1;

        globals.tbl_name = xrealloc(globals.tbl_name, (sizeof (char) * tbl_name_sz));

        memset(globals.tbl_name, '\0', tbl_name_sz);
        strcpy(globals.tbl_name, tbl_name);

        globals.tbl_name[tbl_name_sz - 1] = '\0';
        tbl_name = NULL;
    }
    //
    tbl_name_prefix = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "table-name-prefix", &tbl_name_prefix))
    {
        snprintf(msg, sz, "%s", "Using default value of 'table-name-prefix'");
        writeToStoreLog(msg);
    }
    else
    {
        int tbl_name_prefix_sz = strlen(tbl_name_prefix) + 1;

        globals.tbl_name_prefix = xrealloc(globals.tbl_name_prefix, (sizeof (char) * tbl_name_prefix_sz));

        memset(globals.tbl_name_prefix, '\0', tbl_name_prefix_sz);
        strcpy(globals.tbl_name_prefix, tbl_name_prefix);

        globals.tbl_name_prefix[tbl_name_prefix_sz - 1] = '\0';
        tbl_name_prefix = NULL;
    }
    //
    tramount_field_name = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "traffic-field-name", &tramount_field_name))
    {
        snprintf(msg, sz, "%s", "Using default value of 'traffic-field-name'");
        writeToStoreLog(msg);
    }
    else
    {
        int tramount_field_name_sz = strlen(tramount_field_name) + 1;

        globals.tramount_field_name = xrealloc(globals.tramount_field_name, (sizeof (char) * tramount_field_name_sz));

        memset(globals.tramount_field_name, '\0', tramount_field_name_sz);
        strcpy(globals.tramount_field_name, tramount_field_name);

        globals.tramount_field_name[tramount_field_name_sz - 1] = '\0';
        tramount_field_name = NULL;
    }
    //
    timestamp_field_name = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "timestamp-field-name", &timestamp_field_name))
    {
        snprintf(msg, sz, "%s", "Using default value of 'timestamp-field-name'");
        writeToStoreLog(msg);
    }
    else
    {
        int timestamp_field_name_sz = strlen(timestamp_field_name) + 1;

        globals.timestamp_field_name = xrealloc(globals.timestamp_field_name, (sizeof (char) * timestamp_field_name_sz));

        memset(globals.timestamp_field_name, '\0', timestamp_field_name_sz);
        strcpy(globals.timestamp_field_name, timestamp_field_name);

        globals.timestamp_field_name[timestamp_field_name_sz - 1] = '\0';
        timestamp_field_name = NULL;
    }

    //
    srcip_field_name = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "srcip-field-name", &srcip_field_name))
    {
        snprintf(msg, sz, "%s", "Using default value of 'srcip-field-name'");
        writeToStoreLog(msg);
    }
    else
    {
        int srcip_field_name_sz = strlen(srcip_field_name) + 1;

        globals.srcip_field_name = xrealloc(globals.srcip_field_name, (sizeof (char) * srcip_field_name_sz));

        memset(globals.srcip_field_name, '\0', srcip_field_name_sz);
        strcpy(globals.srcip_field_name, srcip_field_name);

        globals.srcip_field_name[srcip_field_name_sz - 1] = '\0';
        srcip_field_name = NULL;
    }
    //
    senderip_field_name = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "senderip-field-name", &senderip_field_name))
    {
        snprintf(msg, sz, "%s", "Using default value of 'senderip-field-name'");
        writeToStoreLog(msg);
    }
    else
    {
        int senderip_field_name_sz = strlen(senderip_field_name) + 1;

        globals.senderip_field_name = xrealloc(globals.senderip_field_name, (sizeof (char) * senderip_field_name_sz));

        memset(globals.senderip_field_name, '\0', senderip_field_name_sz);
        strcpy(globals.senderip_field_name, senderip_field_name);

        globals.senderip_field_name[senderip_field_name_sz - 1] = '\0';
        senderip_field_name = NULL;
    }
    //
    ident_field_name = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "ident-field-name", &ident_field_name))
    {
        snprintf(msg, sz, "%s", "Using default value of 'ident-field-name'");
        writeToStoreLog(msg);
    }
    else
    {
        int ident_field_name_sz = strlen(ident_field_name) + 1;

        globals.ident_field_name = xrealloc(globals.ident_field_name, (sizeof (char) * ident_field_name_sz));

        memset(globals.ident_field_name, '\0', ident_field_name_sz);
        strcpy(globals.ident_field_name, ident_field_name);

        globals.ident_field_name[ident_field_name_sz - 1] = '\0';
        ident_field_name = NULL;
    }

    //
    rule_field_name = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "rule-field-name", &rule_field_name))
    {
        snprintf(msg, sz, "%s", "Using default value of 'rule-field-name'");
        writeToStoreLog(msg);
    }
    else
    {
        int rule_field_name_sz = strlen(rule_field_name) + 1;

        globals.rule_field_name = xrealloc(globals.rule_field_name, (sizeof (char) * rule_field_name_sz));

        memset(globals.rule_field_name, '\0', rule_field_name_sz);
        strcpy(globals.rule_field_name, rule_field_name);

        globals.rule_field_name[rule_field_name_sz - 1] = '\0';
        rule_field_name = NULL;
    }

    //
    desc_field_name = xmalloc(sizeof (char) * CFG_PARAM_LEN);

    if (!config_lookup_string(cf, "desc-field-name", &desc_field_name))
    {
        snprintf(msg, sz, "%s", "Using default value of 'desc-field-name'");
        writeToStoreLog(msg);
    }
    else
    {
        int desc_field_name_sz = strlen(desc_field_name) + 1;

        globals.desc_field_name = xrealloc(globals.desc_field_name, (sizeof (char) * desc_field_name_sz));

        memset(globals.desc_field_name, '\0', desc_field_name_sz);
        strcpy(globals.desc_field_name, desc_field_name);

        globals.desc_field_name[desc_field_name_sz - 1] = '\0';
        desc_field_name = NULL;
    }

    /*
     * end of readConfig
     */
    config_destroy(cf);
}
