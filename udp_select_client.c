/*
 * =====================================================================================
 *
 *       Filename:  udp_select_client.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/08/2014 04:52:46 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Andy.S.Y.Chen (), andysychen@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_LINE 80
#define PORT 8000

int main(int argc, char *argv[]) 
{
	struct sockaddr_in sin, cin;
	socklen_t addr_len;

	int sockfd, maxfdp;
	char *msg = "client";
	char buf[MAX_LINE];

	fd_set fds;
	struct timeval timeout;
	int interval = 3;

	bzero(&sin, sizeof(sin));

	sin.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);
	sin.sin_port = htons(PORT);

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("fail to create socket.\n");
		exit(1);
	}
	
	addr_len = sizeof(cin);
	
	while (1) {

		timeout.tv_usec = 0;
		timeout.tv_sec = interval;

		FD_ZERO(&fds);
		FD_SET(sockfd, &fds);

		maxfdp = sockfd + 1;
	
		sendto(sockfd, msg, strlen(msg) + 1, 0, (struct sockaddr*)&sin, sizeof(sin));

		switch(select(maxfdp, &fds, NULL, NULL, &timeout)) {
			case -1: 
				perror("error");
				exit(-1);	
				break;

			case 0:
				printf("timeout.\n");
				break;

			default:
				if (FD_ISSET(sockfd, &fds)) {

					if (recvfrom(sockfd, buf, MAX_LINE, 0, (struct sockaddr *)&cin, &addr_len) < 0) {
						perror("fail to receive.\n");
						exit(1);
					}
					else {
						printf("receive from server: %s.\n", buf);
			
						if (close(sockfd) < 0) {
						    perror("fail to close.\n");
						    exit(1);
						}
						return 0;
					}
				}
				break;
		}

	}
}


