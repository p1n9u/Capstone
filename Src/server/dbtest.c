#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/include/mysql/mysql.h"

#define BUF_SIZE 1024

const char *host = "localhost";
const char *user = "root";
const char *pw = "asdf1234.";
const char *db = "ecgdb";
char query[BUF_SIZE];

int main() {
	printf("my sql version : %s\n", mysql_get_client_info());

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

		for ( i=0; i<10; i++ ) {
			sprintf(query, "update ecgtb set analog=%d where num=%d", i, i);
			state = mysql_query(connection, query);
			if ( state != 0 ) {
				printf("update\n");
				return 1;
			}
		}

		sprintf(query, "select * from ecgtb where num<10");

		state = mysql_query(connection, query);
		if ( state == 0 ) {
			sql_result = mysql_store_result(connection);
			while ( (sql_row = mysql_fetch_row(sql_result)) != NULL ) {
				printf("%s %s %s %s %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
			}
			mysql_free_result(sql_result);
		}
		mysql_close(connection);
	}

	return 0;

}
