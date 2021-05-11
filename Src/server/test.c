#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/sendfile.h>

#define DEFAULT_PROTOCOL 0
#define MAXLINE 100
#define BACKLOG 5
#define TRUE 1

int main(int argc, char* argv[]) {
    int fd, size, sfd, cfd, port;
    struct sockaddr_in server_addr, client_addr;
    struct stat data;
    socklen_t client_len;
    char *haddrp, inmsg[MAXLINE], outmsg[MAXLINE];

    if ( argc != 2 ) {
        fprintf(stderr, "usage : %s <port>\n", argv[0]);
        exit(1);
    }

    port = atoi(argv[1]);
    sfd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);
    bind(sfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
    listen(sfd, BACKLOG);

    while(TRUE) {
        client_len = sizeof(client_addr);
        if((cfd = accept(sfd, (struct sockaddr *) &client_addr, &client_len)) < 0)
	{ perror("accept error"); }
	printf("ok");
        haddrp = inet_ntoa(client_addr.sin_addr);
        printf("server : %s (%d) connected\n", haddrp, client_addr.sin_port);
        recv(cfd, inmsg, MAXLINE, 0);
        switch ( fork() ) {
            case -1 :
                perror("fork");
                exit(1);
            case 0 :
                printf("%s\n", inmsg);
                close(cfd);
                exit(0);
            default :
                close(cfd);
        }
    }
    return 0;
}
