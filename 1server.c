#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void getclientdata(int connfd) {
	char buff[MAX];
	
	while (1) {
	bzero(buff, MAX);
	read(connfd, buff, sizeof(buff));
	printf("%s", buff);
	bzero(buff, MAX);
	scanf("%s\n", buff);
	write(connfd, buff, sizeof(buff));
	bzero(buff, MAX);
	}
}

int main() {
	printf("main");
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr)); 

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	len = sizeof(cli);
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
    }
    else
        printf("Socket successfully binded..\n");
	
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");

	connfd = accept(sockfd, (SA*)&cli, &len); 

	getclientdata(connfd);

	close(sockfd);
}
