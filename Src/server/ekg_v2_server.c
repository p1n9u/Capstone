/* include library */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "/usr/include/mysql/mysql.h"

/* define macro */
#define DEFAULT_PROTOCOL 0
#define DATA_CNT 4
#define DATA_LEN 32
#define BUF_SIZE 1024
#define Q_SIZE 128
#define TRUE 1
#define FALSE 0

/* declare global */
const char *host = "localhost";
const char *user = "root";
const char *pw = "asdf1234.";
const char *db = "testdb";
char query[Q_SIZE];
char usr[DATA_LEN];
char buf[BUF_SIZE];
int usr_flag = FALSE;

int read_buf(int, char *);

/* main */
int main(int argc, char *argv[]) {

	int clen, sfd, cfd, n;
	struct sockaddr_in saddr, caddr;
	char *haddrp;

	if ( argc != 2 ) {
		printf("input port err\n");
		exit(0);
	}

	if ( (sfd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL)) == -1 ) {
		printf("sfd socket err\n");
		exit(0);
	}

	memset(&saddr, 0x00, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(atoi(argv[1]));

	if ( bind(sfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0 ) {
		printf("sfd bind err\n");
		exit(0);
	}

	if ( listen(sfd, 5) < 0 ) {
		printf("sfd listen err\n");
		exit(0);
	}

	memset(buf, '\0', sizeof(buf));
	printf("==================================================\n");
	printf("[ waiting for connection request ]\n");

	while(TRUE) {
		clen = sizeof(caddr);
		cfd = accept(sfd, (struct sockaddr *) &caddr, (socklen_t *) &clen);

		if ( cfd < 0 ) {
			printf("cfd accept err\n");
			exit(0);
		}

		haddrp = inet_ntoa(caddr.sin_addr);
		printf("    >> client : %s(%d) connected\n", haddrp, caddr.sin_port);

		while(TRUE) {
			int status, fd[2];
			pipe(fd);
			pid_t pid;
			pid = fork();
			if ( usr_flag == FALSE ) {
				if ( pid == 0 ) {
					printf("[ waiting for usr input... ]\n");
					n = read(cfd, buf, sizeof(buf));
					write(fd[1], buf, sizeof(buf));
					exit(0);
				} else {
					waitpid(pid, &status, 0);
					read(fd[0], buf, sizeof(buf));
					sprintf(usr,"%s", buf);
					printf("    >> usr name passed : (%s)\n", usr);
					printf("==================================================\n");
					usr_flag = TRUE;
				}
			} else {
				if ( pid == 0 ) {
					n = read(cfd, buf, sizeof(buf));
					printf("[%s]$ %s\n", usr, buf);
					exit(0);
				} else {
					waitpid(pid, &status, 0);
				}
			}

		}
		printf("exit\n");
		close(cfd);

	}

	close(sfd);
	return 0;

}

int read_buf(int fd, char *str) {
	int n;
	do {
		n = read(fd, str, 1);
	} while ( n > 0 && *str++ != 0x00 );
	return ( n > 0 );
}

/*
	while(1) {
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

*/
