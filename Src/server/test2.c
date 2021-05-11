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
#define MAXLINE 1024

int main(int argc, char* argv[]) {
    int fd, sfd, port, result, size;
    struct sockaddr_in server_addr;
    struct hostent *hp;
    char *f, *haddrp, *host, inmsg[MAXLINE], outmsg[MAXLINE];

    if ( argc != 3 ) {
        fprintf(stderr, "usage : %s <host> <port>\n", argv[0]);
        exit(1);
    }

    host = argv[1];
    port = atoi(argv[2]);
    sfd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, host, &server_addr.sin_addr);
    server_addr.sin_port = htons(port);

    do {
        result = connect(sfd, (struct sockaddr *) &server_addr, sizeof(server_addr));
        if ( result == -1 ) {
            sleep(1);
        }
    } while ( result == -1 );

    printf("input : ");
    scanf("%s", inmsg);
    send(sfd, inmsg, MAXLINE, 0);
    close(sfd);
    exit(0);
}
