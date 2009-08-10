#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void serial_read(char* serchars)
{
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

int main (int argc, char *argv[])
{
	char serialreadchars[9+1];
	int span;
	float value;
	char unit[2+1];
	
	serialreadchars[9]= '\0';
	serial_read(serialreadchars);
	span=read_span(serialreadchars);
	value=read_value(serialreadchars,span);
	get_unit(serialreadchars,span,unit);

// display the stuff
	printf ("Messung: %f%s\n",value,unit);
//		01009;80:
	return 0;

}
