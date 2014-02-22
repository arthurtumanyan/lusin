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

typedef void Sigfunc(int);

Sigfunc * signal(int signo,
                 Sigfunc * func)
{
    struct sigaction act, oact;


    act.sa_handler = func;

    sigemptyset(&act.sa_mask);

    act.sa_flags = 0;

    if (sigaction(signo, &act, &oact) < 0)
    {
        return (SIG_ERR);
    }

    return (oact.sa_handler);
}

/* end signal */
Sigfunc * Signal(int signo,
                 Sigfunc * func) /* for our signal() function */
{
    Sigfunc * sigfunc;

    if ((sigfunc = signal(signo, func)) == SIG_ERR)
    {
        // todo
    }

    return (sigfunc);
}

void signal_term(int sig)
{
    writeToStoreLog("Caught TERM signal");
    halt();
}

void signal_hup(int sig)
{
    writeToStoreLog("Caught HUP signal, reconfiguring...");
    readConfig(arguments.configfile);
}

void set_sig_handler()
{

    Signal(SIGINT, signal_term);
    Signal(SIGHUP, signal_hup);
    Signal(SIGUSR1, SIG_IGN);
    Signal(SIGUSR2, SIG_IGN);
    Signal(SIGTRAP, SIG_IGN);
    Signal(SIGCHLD, SIG_IGN);
    Signal(SIGTSTP, SIG_IGN);
    Signal(SIGTTOU, SIG_IGN);
    Signal(SIGTTIN, SIG_IGN);
    Signal(SIGABRT, SIG_IGN);
    Signal(SIGPIPE, SIG_IGN);
    Signal(SIGALRM, SIG_IGN);
    Signal(SIGSEGV, SIG_IGN);
    Signal(SIGBUS, SIG_IGN);
    Signal(SIGWINCH, SIG_IGN);
    Signal(SIGTERM, signal_term);
}
