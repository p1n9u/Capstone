/* library */
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
#include "/usr/include/mysql/mysql.h"

/* define */
#define DEFAULT_PROTOCOL 0
#define DATA_CNT 21
#define DATA_LEN 32
#define BUF_SIZE 1024
#define Q_SIZE 128

/* global */
const char *host = "localhost";
const char *user = "root";
const char *pw = "asdf1234.";
const char *db = "testdb";
char query[Q_SIZE];

/* func proto */
int readLine(int , char *);

/* main */
int main(int argc, char *argv[]) {
	int fd, sfd, cfd, port, cLen, size;
	char recv_msg[BUF_SIZE], send_msg[BUF_SIZE];
	struct sockaddr_in saddr, caddr;
	struct hostent *hp;
	char *haddrp, *path, *f;

	char delimeter[] = "|";
	char *result;
	char parsing[DATA_CNT][DATA_LEN];


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
			memset(&recv_msg, '\0', BUF_SIZE);
			readLine(cfd, recv_msg);
			//printf("%s\n", recv_msg);

			int i;
			result = strtok(recv_msg, delimeter);
			while ( result != NULL ) {
				strcpy(parsing[i++], result);
				result = strtok(NULL, delimeter);
			}

			for ( i=0; i<DATA_CNT; i++ ) {
				printf("[%d] : %s\n", i, parsing[i]);
			}
			
			close(cfd);
			exit(0);

			MYSQL *connection = NULL;
        		MYSQL conn;
        		MYSQL_RES *sql_result;
        		MYSQL_ROW sql_row;

			if ( mysql_init(&conn) == NULL ) {
		                printf("mysql_init()\n");
                		return 1;
        		}

			connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);

			if ( connection == NULL ) {
		                printf("connection\n");
                		return 1;
			} else {
                		printf("connection success\n");
                		int i, state = 0;

				if ( mysql_select_db(&conn, db)) {
                        		printf("db\n");
                        		return 1;
                		}

				printf("%s before data input\n", parsing[0]);
			 	sprintf(query, "select * from %s where num<10", parsing[0]);
				state = mysql_query(connection, query);
                                if ( state == 0 ) {
                                        sql_result = mysql_store_result(connection);
                                        while ( (sql_row = mysql_fetch_row(sql_result)) != NULL ) {
                                                printf("%s %s %s %s %s %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[5]);
                                        }
                                        mysql_free_result(sql_result);
                                }

				printf("updating data...\n");
				for ( i=0; i<DATA_CNT/2; i++ ) {
                        		sprintf(query, "update %s set analog=%s where num=%d", parsing[0], parsing[i*2+1], i);
                       			state = mysql_query(connection, query);
                        		if ( state != 0 ) {
                                		printf("update analog err\n");
                                		return 1;
                        		}
                		}
				for ( i=0; i<DATA_CNT/2-1; i++ ) {
//					printf("data check %.8f", atof(parsing[i*2+2]));
					sprintf(query, "update %s set sec=%s where num=%d", parsing[0],parsing[i*2+2], i);
					state = mysql_query(connection, query);
					if ( state != 0 ) {
						printf("update sec err\n");
						return 1;
					}

				}


				printf("%s after data input\n", parsing[0]);
				sprintf(query, "select * from %s where num<10", parsing[0]);
				state = mysql_query(connection, query);
                		if ( state == 0 ) {
                        		sql_result = mysql_store_result(connection);
                        		while ( (sql_row = mysql_fetch_row(sql_result)) != NULL ) {
                                		printf("%s %s %s %s %s %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4],sql_row[5]);
                        		}
                      	 		mysql_free_result(sql_result);
                		}
				mysql_close(connection);
        		}
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
