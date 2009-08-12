#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <termios.h> /* POSIX terminal control definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

void serial_read(char* serchars, int devfd)
{
	int nbytes=0;
	char bufptr[128];
	nbytes += read(devfd,bufptr, 1);
	strncpy(serchars,"01009;80:",9);
	return;
}
float read_value(serialreadchars,span)
{
	return 0.0;	
}
int read_span(char* serchars)
{
	return;
}

void get_unit(char* serchars, int span, char* unit)
{
	switch (serchars[5])
	{
		case ';' :
			strcpy(unit,"V");
			break;
		case '9' :
		      	strcpy(unit,"A");
			break;
		default:
			break;
	return;

	}
}
/*
 *
1.009 V DC        01009;80:<\r><\n>
-1.008 V DC       01008;<0:<\r><\n>
-1.008 V DC + DC  01008;<0:<\r><\n>
0.010 V AC        00010;806<\r><\n>
13.4 Ohm          001343802<\r><\n>
0.034 nF          000346802<\r><\n>
20 °C             000204800<\r><\n>
0.06 A DC         000069808<\r><\n>   (ca. alle 600 ms)
64.7 mA DC        10647?80:<\r><\n>
*
*/
int serial_init (char* dev)
{
	struct termios options;
	int fd; /* File descriptor for the port */
	fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1)
		perror("open_port: Unable to open port ");
	else
		fcntl(fd, F_SETFL, 0);

	tcgetattr(fd, &options);
	cfsetispeed(&options, B1200);
	cfsetospeed(&options, B1200);

	options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	tcsetattr(fd, TCSANOW, &options);
	return (fd);		
}
int main (int argc, char *argv[])
{
	char serialreadchars[9+1];
	int span;
	float value;
	char unit[2+1];
	char serdev[] = "/dev/ttyS0";
	int devfd;

	devfd=serial_init(serdev);
	serialreadchars[9]= '\0';
	serial_read(serialreadchars,devfd);
	span=read_span(serialreadchars);
	value=read_value(serialreadchars,span);
	get_unit(serialreadchars,span,unit);

// display the stuff
	printf ("Messung: %f%s\n",value,unit);
//		01009;80:
	close(devfd);
	return 0;

}
