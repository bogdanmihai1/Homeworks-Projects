#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "helpers.h"

void usage(char *file)
{
    fprintf(stderr, "Usage: %s id_client server_address server_port\n", file);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, n, ret, id_len, fdmax;
    char* client_id;
    struct sockaddr_in serv_addr;
    char buffer[BUFLEN];
    fd_set fds;
    fd_set tmp_fds;

    if (argc < 4) {
        usage(argv[0]);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    DIE(sockfd < 0, "socket");

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[3]));
    ret = inet_aton(argv[2], &serv_addr.sin_addr);
    DIE(ret == 0, "inet_aton");

    ret = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
    DIE(ret < 0, "connect");

    FD_SET(0, &fds);
    FD_SET(sockfd, &fds);
    fdmax = sockfd;
    FD_ZERO(&tmp_fds);

    // se trimite id-ul
    client_id = argv[1];
    id_len = strlen(client_id);
    n = send(sockfd, client_id, id_len, 0);
    DIE(n < 0, "send_id");

    while (1) {
        tmp_fds = fds;
        ret = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
        DIE(ret < 0, "select");

        if (FD_ISSET(0, &tmp_fds)) {
            memset(buffer, 0, BUFLEN);
            // se citeste comanda
            fgets(buffer, BUFLEN - 1, stdin);

            if (strncmp(buffer, "exit", 4) == 0) {
                break;
            }

            // se trimite mesajul catre server
            n = send(sockfd, buffer, strlen(buffer), 0);
            DIE(n < 0, "send");
       }
    }

    close(sockfd);

    return 0;
}
