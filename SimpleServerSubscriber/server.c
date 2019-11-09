#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "helpers.h"

struct Subscriber{
	char* id;
	char* topics[50];
	int SF[50];
	int cnt;
};

void usage(char *file)
{
	fprintf(stderr, "Usage: %s server_port\n", file);
	exit(0);
}

void subscribe(char* topic, struct Subscriber* subscriber, int SF) {
	int i;
	for (i = 0; i < subscriber->cnt; i++) {
		if (strcmp(topic, subscriber->topics[i]) == 0) {
			perror("Already subscribed");
			return;
		}
	}
	if (subscriber->cnt < 50) {
		strcpy(subscriber->topics[subscriber->cnt], topic);
		subscriber->SF[subscriber->cnt] = SF;
		subscriber->cnt++;
		printf("Succesfully subscribed to %s.\n", topic);
	} else {
		perror("Too many topics");
	}
}

void unsubscribe(char* topic, struct Subscriber* subscriber) {
	int i, pos;
	for (i = 0; i < subscriber->cnt; i++) {
		if (strcmp(topic, subscriber->topics[i]) == 0) {
			pos = i;
			subscriber->cnt--;
			strcpy(subscriber->topics[pos], subscriber->topics[subscriber->cnt]);
			subscriber->SF[pos] = subscriber->SF[subscriber->cnt];
			printf("Succesfully unsubscribed from %s.\n", topic);
			return;
		}
	}
	perror("Not subscribed");
}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno, curr_subscriber = 0, chk;
	int n, i, ret, fdmax;
	struct Subscriber subscribers[50];
	struct sockaddr_in serv_addr, cli_addr;
	char buffer[BUFLEN];
	socklen_t clilen;

	fd_set read_fds;
	fd_set tmp_fds;
	
	if (argc < 2) {
		usage(argv[0]);
	}

	FD_ZERO(&read_fds);
	FD_ZERO(&tmp_fds);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	DIE(sockfd < 0, "socket");

	portno = atoi(argv[1]);
	DIE(portno == 0, "atoi");

	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr));
	DIE(ret < 0, "bind");

	ret = listen(sockfd, MAX_SUBS);
	DIE(ret < 0, "listen");

	// se adauga noul file descriptor (socketul pe care se asculta conexiuni) in multimea read_fds
	FD_SET(sockfd, &read_fds);
	fdmax = sockfd;

	while (1) {
		tmp_fds = read_fds; 
		
		ret = select(fdmax + 1, &tmp_fds, NULL, NULL, NULL);
		DIE(ret < 0, "select");

		for (i = 0; i <= fdmax; i++) {
			if (FD_ISSET(i, &tmp_fds)) {
				if (i == sockfd) {
					// new socket
					clilen = sizeof(cli_addr);
					newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
					DIE(newsockfd < 0, "accept");

					FD_SET(newsockfd, &read_fds);
					if (newsockfd > fdmax) { 
						fdmax = newsockfd;
					}

					chk = 0;
				} else {
					// s-au primit date pe unul din socketii de subscriber
					int sf;
					char* subscriber_topic;
					char* buff_cpy;

					if(chk == 0) {
						// chk verifica daca mesajul primit este id-ul sau nu
						chk = 1;
						memset(buffer, 0, BUFLEN);
						n = recv(i, buffer, sizeof(buffer), 0);
						DIE(n < 0, "subscriber");

						subscribers[curr_subscriber++].id = buffer;
						printf("New subscriber %s connected from %s:%d.\n", subscribers[curr_subscriber - 1].id,
							inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
					}
					memset(buffer, 0, BUFLEN);
					n = recv(i, buffer, sizeof(buffer), 0);
					DIE(n < 0, "recv");

					if (n == 0) {
						// conexiunea s-a inchis
						printf("Client %s disconnected.\n", subscribers[curr_subscriber - 1].id);
						close(i);
						FD_CLR(i, &read_fds);
					} else {
						// se verifica cererea subscriberului
					    buff_cpy = strtok(buffer, " ");
					    if (strncmp(buff_cpy, "subscribe", 9) == 0) {
					    	buff_cpy = strtok(NULL, " ");
					    	subscriber_topic = buff_cpy;
					    	buff_cpy = strtok(NULL, " ");
					    	if (buff_cpy != NULL) {
					    		sf = buff_cpy[0] - '0';

					    		if (sf == 0 || sf == 1) {
						    		subscribe(subscriber_topic, &subscribers[i], sf);
					    		} else {
						    		perror("Invalid SF");
						    	}
						    } else {
						    	perror("No SF");
						    }
					    } else if(strncmp(buff_cpy, "unsubscribe", 11) == 0) {
					    	buff_cpy = strtok(NULL, " ");
					    	subscriber_topic = buff_cpy;
					    	unsubscribe(subscriber_topic, &subscribers[i]);
					    } else {
					    	perror("Invalid command");
					    }
                    }
				}
			}
		}
	}

	close(sockfd);

	return 0;
}
