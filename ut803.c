#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int serial_read(char* serchars)
{
	return VOLTS;
}
float read_value(serialreadchars,span)
{
	return 0.0;	
}
void serial_read(char* serchars)
{
	return;
}

void get_unit(char* serchars, int span, char* unit)
{
	return;
}
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
