#include <mysql.h>
#include "PJ_RPI.h"
#include <stdio.h>
#include <time.h>

char cmd[100];
char datetime[19];
int gpioArray[27];

int main()
{
	// Initiation of a connection handle structure
	MYSQL *con = mysql_init(NULL);
	if (con == NULL)
  	{
		fprintf(stderr, "%s\n", mysql_error(con));
		exit(1);
  	}
	// Creation of a connection
	if (mysql_real_connect(con, "localhost", "root", "", "ioLogging", 0, NULL, 0) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}

	if(map_peripheral(&gpio) == -1) 
	{
		printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
		return -1;
    }

	while(1)
	{
		for(int x = 1; x <= 27; x++) {
			INP_GPIO(x);
			int value = GPIO_READ(x);
			value = value ? 1 : 0;
			if(gpioArray[x-1] != value) {
				usleep(100000);		// sleep for 100ms because bounce
				time_t t = time(NULL);
				struct tm tm = *localtime(&t);
				sprintf(datetime, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
				sprintf(cmd, "INSERT INTO gpio VALUES(%d, %d, \"%s\")", x, value, datetime);
				printf("%s\n", cmd);
				if (mysql_query(con, cmd))
				{
					fprintf(stderr, "%s\n", mysql_error(con));
					mysql_close(con);
					exit(1);
				}
			}
			gpioArray[x-1] = value;
		}
	}
  	mysql_close(con);
	return 0;	
}
