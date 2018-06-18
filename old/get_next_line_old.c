/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhohls <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 07:39:12 by rhohls            #+#    #+#             */
/*   Updated: 2018/06/06 07:05:59 by rhohls           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"


#include <stdio.h>

ssize_t read(int fildes, void *buf, size_t nbyte);

/*
 * If successful, the number of bytes actually read is returned.  Upon read-
     ing end-of-file, zero is returned.  Otherwise, a -1 is returned and the
     global variable errno is set to indicate the error.
*/

/*
** str iso: returns new string from str[0] until char c
*/

char	*ft_striso(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			break ;
		i++;
	}
	return (ft_strsub(str, 0, i));
}

char	*ft_strjoinfree(char *s1, char *s2)
{
	char *str_new;

	if (s1 == NULL)
		return (s2);
	else if (s2 == NULL)
		return (s1);
	if (!(str_new = ft_strnew(ft_strlen(s1)
					+ ft_strlen(s2) + 1)))
		return (NULL);
	ft_strcpy(str_new, s1);
	ft_strcpy((str_new + ft_strlen(s1)), (char *)s2);
	free(&(*s1));
	free(&(*s2));
	return (str_new);
}

int get_next_line(const int fd, char **line)
{
//	printf("1");
	if (BUFF_SIZE <= 0)
		return (-1);

	int			read_ret;
	static char	*strhold;
	char		*newstr;
	char		*strtemp;

	if (strhold)
	{
		if (ft_strchr(strhold, '\n'))
		{
			*line = ft_striso(strhold, '\n');
			strhold = ft_strchr(strhold, '\n');
			strhold++;
			return 1;
		}
//		else if (ft_strchr(strhold, '\0'))
	}
	int i = 0;
	while (1)
	{
		newstr = ft_strnew(BUFF_SIZE);//free after join
		if ((read_ret = read(fd, newstr, BUFF_SIZE)) == -1)
			return (-1);
		strtemp = strhold;
		strhold = ft_strjoinfree(strtemp, newstr);
//		strhold = ft_strjoinfree(strhold, newstr);
		
		
		if (read_ret < BUFF_SIZE)// && ft_strchr(strhold, '\0'))
		{
			*line = strhold;
			return 0;
		}
//		free(&(*strtemp));
		else if (ft_strchr(strhold, '\n'))
		{
			*line = ft_striso(strhold, '\n');
			strhold = ft_strchr(strhold, '\n');
			strhold++;
			/*
			//if (*strhold == 0 || *strhold == 4 || *strhold == 3)
			if (read_ret == 0)
			{
				printf("123");
				return 0;
			}*/
			return 1;
		}


		i++;
	}  
	return -1;
}





