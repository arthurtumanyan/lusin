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
#include <mysql/mysql.h>

MYSQL * handle;

void CONNECT_TO_DB()
{
    int sz = 128;
    char msg[sz];

    handle = mysql_init(NULL);

    if (handle == NULL)
    {
        snprintf(msg, sz, "%s", mysql_error(handle));
        writeToStoreLog(msg);
        halt();
    }

    if (mysql_real_connect(handle, globals.db_host, globals.db_user, globals.db_password, globals.db_name, globals.db_port, NULL, 0) == NULL)
    {
        snprintf(msg, sz, "%s", mysql_error(handle));
        writeToStoreLog(msg);
        halt();
    }

}

void WRITE_TO_DB(double tr_amount, long ts, char *desc, char *rule, char *ident, char * srcip, char * senderip)
{

    int sz = 128;
    char msg[sz];
    int query_sz = 256;
    char query[query_sz];

    snprintf(query, query_sz, "INSERT INTO `%s_%s` (`%s`,`%s`,`%s`,`%s`,`%s`,`%s`,`%s`,`client_start_ts`) VALUES('%0.4f','%ld','%s','%s','%s','%s','%s','%ld');",
             globals.tbl_name_prefix,
             globals.tbl_name,
             globals.tramount_field_name,
             globals.timestamp_field_name,
             globals.desc_field_name,
             globals.ident_field_name,
             globals.rule_field_name,
             globals.srcip_field_name,
             globals.senderip_field_name,
             tr_amount, ts, desc, ident, rule, srcip, senderip, start_time
             );

    if (mysql_query(handle, query) != 0)
    {
        snprintf(msg, sz, "%s", mysql_error(handle));
        writeToStoreLog(msg);
    }
    else
    {
        addToBackupFile(query);
    }


}

void CLOSE_DB()
{
    if (handle)
    {
        mysql_close(handle);
    }
}