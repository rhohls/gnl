/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhohls <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 11:18:29 by rhohls            #+#    #+#             */
/*   Updated: 2018/06/11 07:58:27 by rhohls           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <project.h>
//# include <fw.h>
# include <string.h>
//# include <strings.h>
# include <stdlib.h>
# include <unistd.h>
//# include <ctype.h>
# include <math.h>
//# include "./get_next_line.h"
# include <stdio.h>
//# include <fcntl.h>
//# include <regex.h>
# include <assert.h>


int get_next_line(const int fd, char **line);
int main()
{
	char 	*line = NULL;
	int		out;
	int		p[2];
	int		fd;
	int		gnl_ret;

	out = dup(1);
	pipe(p);

	fd = 1;
	dup2(p[1], fd);
	write(fd, "abc\n\n", 5);
	close(p[1]);
	dup2(out, fd);

	printf("test start\n");
	/* Read abc and new line */
//	printf("curr gnl line |%s| address %p \n",line, line);
	gnl_ret = get_next_line(p[0], &line);
//	printf("curr gnl |%i| line |%s| address %p \n", gnl_ret, line, line);
	if(gnl_ret == 1)
	{
		if(strcmp(line, "abc") == 0)
			printf("line 1 good\n");
	}

	/* Read new line */
	gnl_ret = get_next_line(p[0], &line);
//	printf("2curr gnl line |%s| address %p \n",line, line);
	if(gnl_ret == 1)
	{
		if(line == NULL || *line == '\0')
			printf("line 2 good\n");
	}

	/* Read again, but meet EOF */
	gnl_ret = get_next_line(p[0], &line);
	if(gnl_ret == 0)
	{
		if(line == NULL || *line == '\0')
			 printf("line 3 good\n");
	}

	/* Let's do it once again */
	gnl_ret = get_next_line(p[0], &line);
	if(gnl_ret == 0)
	{
		if(line == NULL || *line == '\0')
			 printf("line 4 good\n");
	}
}


