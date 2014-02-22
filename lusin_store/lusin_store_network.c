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
#include "lusin_store_protocol.h"

#define MAX_MSG_SIZE 1024

void do_listen()
{
    char msg[64];

    memset(msg, '\0', 64);

    int sockfd, n;

    struct sockaddr_in servaddr, cliaddr;


    socklen_t len;
    struct hostent * hostp;
    char * client_addr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof (servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(globals.listen_host);
    servaddr.sin_port = htons(globals.listen_port);

    bind(sockfd, (struct sockaddr*) &servaddr, sizeof (servaddr));

    TrafficInfo * info;
    uint8_t buf[MAX_MSG_SIZE];

    while (!listen_stop_flag)
    {
        len = sizeof (cliaddr);
        n = recvfrom(sockfd, buf, MAX_MSG_SIZE, 0, (struct sockaddr*) &cliaddr, &len);
        buf[n] = 0;
        info = traffic_info__unpack(NULL, n, buf);

        if (info == NULL)
        {
            snprintf(msg, 64, "Unable unpack received message");
            writeToStoreLog(msg);
            continue;
        }
        hostp = gethostbyaddr((const char *) &cliaddr.sin_addr.s_addr, sizeof (cliaddr.sin_addr.s_addr), AF_INET);
        if (hostp != NULL)
        {

            client_addr = inet_ntoa(cliaddr.sin_addr);
            if (client_addr == NULL)
                client_addr = "0.0.0.0";
        }

        WRITE_TO_DB(info -> amount, info -> timestamp, info -> desc, info -> rule, info -> ident, info->source_addr, client_addr);
    }
    snprintf(msg, 64, "Listening loop broken");
    writeToStoreLog(msg);
    traffic_info__free_unpacked(info, NULL);
}
