#include "../get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
int main (void )
{
	FILE *ptr;
	int fd;
	int r;
	char *s;

	ptr = fopen("one_big_fat_line.txt", "r");
	fd = fileno(ptr);
	s =  (char *)malloc(sizeof(char) * 32);
	while ((r = get_next_line(fd, &s)) > 0)
	{
		printf("%s\n", s);
	}
	fclose (ptr);
	return (0);

}

