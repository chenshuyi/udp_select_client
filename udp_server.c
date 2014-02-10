/*
 * =====================================================================================
 *
 *       Filename:  udp_server.c
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

	int sockfd, n;
	char *msg = "server";
	char buf[MAX_LINE];

	bzero(&sin, sizeof(sin));

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htons(INADDR_ANY);
	sin.sin_port = htons(PORT);

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("fail to create socket.\n");
		exit(1);
	}

	n = bind(sockfd, (struct sockaddr*)&sin, sizeof(sin));
	if (n < 0) {
		perror("fail to bind.\n");
		exit(1);
	}

	while (1) {
		addr_len = sizeof(cin);

		recvfrom(sockfd, buf, MAX_LINE, 0, (struct sockaddr*)&cin, &addr_len);

		sendto(sockfd, msg, strlen(msg) + 1, 0, (struct sockaddr*)&cin, addr_len);
	}
}


