#include "../get_next_line.h"
#include <stdio.h>

int main()
{
    char 	*line = NULL;
    
	if(get_next_line(-99, NULL) == -1)
		printf("bad1");
	if(get_next_line(-1, NULL) == -1)
		printf("bad2");
	if(get_next_line(-10000, NULL) == -1)
		printf("bad3");
	if(get_next_line(1, NULL) == -1)
		printf("bad4");
	if(get_next_line(99, NULL) == -1)
		printf("bad5");

	if(get_next_line(-99, &line) == -1)
		printf("bad6");
	if(get_next_line(-1, &line) == -1)
		printf("bad7");
	if(get_next_line(-10000, &line) == -1)
		printf("bad8");

	/* Not opened fd */
	if(get_next_line(42, &line) == -1)
		printf("bad9");
}

