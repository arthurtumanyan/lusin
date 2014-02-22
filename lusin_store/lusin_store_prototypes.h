/*
 * File:   lusin_prototypes.h
 * Author: arthur
 *
 * Created on July 6, 2013, 9:35 PM
 */

#include "lusin_store.h"

extern void * xmalloc(size_t size);

extern void * xrealloc(void * ptr,
        size_t size);

extern void * xcalloc(size_t nmemb,
        size_t size);

extern FILE * openStoreLog();

extern void closeStoreLog();

extern void writeToStoreLog(char * log_string);

extern void write_syslog(char * msg);

extern void halt();

extern void savePid();

extern int checkPid();

extern void removePid();

extern void readConfig(char * cfile);

extern void set_sig_handler();

extern void CONNECT_TO_DB();
extern void WRITE_TO_DB(double tr_amount, long ts, char *desc, char *rule, char *ident, char *srcip, char * senderip);
extern void CLOSE_DB();
extern void addToBackupFile(char * query_string);