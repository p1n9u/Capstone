#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define DEFAULT_PROTOCOL 0
#define BUF_SIZE 1024

int readLine(int , char *);

int main(int argc, char *argv[]) {
	int fd, sfd, cfd, port, cLen, size;
	char recv_msg[BUF_SIZE], send_msg[BUF_SIZE];
	struct sockaddr_in saddr, caddr;
	struct hostent *hp;
	char *haddrp, *path, *f;

	signal(SIGCHLD, SIG_IGN);

	if ( argc != 2 ) {
		fprintf(stderr, "Usage : %s <port> \n", argv[0]);
		exit(0);
	}

	port = atoi(argv[1]);
	sfd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);

	bzero((char *)&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons((unsigned short)port);

	bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr));
	listen(sfd, 5);

	while(1) {
		cLen = sizeof(caddr);
		cfd = accept(sfd, (struct sockaddr *)&caddr, &cLen);
		haddrp = inet_ntoa(caddr.sin_addr);
		printf("Server : %s(%d) connected.\n", haddrp, caddr.sin_port);

		if ( fork() == 0 ) {
			readLine(cfd, recv_msg);
			printf("%s", recv_msg);
			path = (char *)malloc(30*sizeof(char));
			path = "./test.txt";
			fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if ( write(fd, recv_msg, strlen(recv_msg)+1) == 0 ) {
				printf("done\n");
			}
			close(fd);
			close(cfd);
			exit(0);
		} else {
			close(cfd);
		}
	}
}

int readLine(int fd, char *str) {
	int n;
	do {
		n = read(fd, str, 1);
	} while ( n>0 && *str++ != '\0' );
	return ( n>0 );
}

