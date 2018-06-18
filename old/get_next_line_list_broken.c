/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhohls <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 09:08:12 by rhohls            #+#    #+#             */
/*   Updated: 2018/06/07 10:49:36 by rhohls           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

#include <stdio.h>

/*
** str iso: returns new string from str[0] until char c
*/

static char	*ft_striso(char *str, char c)
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


static t_gnl  *ft_lstnew_gnl(int fd)
{
	t_gnl *new;

	if (!(new = (t_gnl*)ft_memalloc(sizeof(t_gnl))))
		return (NULL);
	new->string = ft_strnew(1);
	new->fd = fd;
	return (new);
}

static char *ft_strjoin_gnl(char *s1, char *s2)
{
	char *str_new;

	if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	if (!(str_new = ft_strnew(ft_strlen(s1)
					+ ft_strlen(s2) + 1)))
		return (NULL);
	ft_strcpy(str_new, s1);
	ft_strcpy((str_new + ft_strlen(s1)), s2);
//	printf("strjoin s1 |%s| \n", s1);
//	free(&(*s1));
	return (str_new);
}

t_gnl *fd_list(t_gnl *listhold, const int fd)
{
	t_gnl			*lstcur;
	t_gnl			*start;
	
	lstcur = NULL;
	start = listhold;

	while (listhold)
	{
//		printf("1");
		if (listhold->fd == fd)
		{
			lstcur = listhold;
			break ;
		}
		if (listhold->next)
			listhold = listhold->next;
		else
			break ;
	}
	if (!lstcur)
	{
		lstcur = ft_lstnew_gnl(fd);
		if (!listhold)
			listhold = lstcur;
		else
			listhold->next = lstcur;
	}
	else
		listhold = start;

	return (lstcur);
}


int get_next_line(const int fd, char **line)
{
	if (BUFF_SIZE <= 0)
		return (-1);
	
	static t_gnl	*listhold;
	t_gnl           *lstcur;
 	t_gnl           *start;	
//	lstcur = fd_list(listhold, fd);
	lstcur = NULL;
	start = listhold;

	while (listhold)
	{
	//		printf("1");
		if (listhold->fd == fd)
		{
			lstcur = listhold;
			break ;
		}
		if (listhold->next)
			listhold = listhold->next;
		else
			break ;
	}
	if (!lstcur)
	{
		lstcur = ft_lstnew_gnl(fd);
		if (!listhold)
			listhold = lstcur;
		else
			listhold->next = lstcur;
	}
	else
		listhold = start;


	char	*strhold;
	char	buffstr[BUFF_SIZE + 1];
	int		read_ret;

	strhold = lstcur->string;
//	printf("my str hold: %s\n",strhold);
	if (strhold)
	{
		if (ft_strchr(strhold, '\n'))
		{
//			printf("previous    \n");
			*line = ft_striso(strhold, '\n');
			strhold = ft_strchr(strhold, '\n');
			strhold++;
			lstcur->string = strhold;
			return 1;
		}
	}
	
//	strhold = ft_strdup("");
	while (TRUE)
	{
		ft_bzero(buffstr, (size_t) BUFF_SIZE);
		if ((read_ret = read(fd, buffstr, BUFF_SIZE)) == -1)
			return (-1);
//		printf("read ret: %i & str read is :%s \n",read_ret, buffstr);
//		printf("str in hold1:%s \n", strhold);

		char *tmp;
		tmp = strhold;
		
		printf("address of temp %p val of temp %p \n", &tmp, tmp);
		printf("address of hold %p val of hold %p \n", &strhold, strhold);
		
		strhold = ft_strjoin_gnl(strhold, buffstr);
		printf("joined \n");	
		
		printf("address of temp %p val of temp %p \n", &tmp, tmp);
		printf("address of hold %p val of hold %p \n", &strhold, strhold);


		printf("str in hold2:%s \n", strhold);	
		printf("str in temp:%s \n", tmp);
		if (tmp)
			free(tmp);
		printf("str in hold3:%s \n", strhold);
		if (read_ret == 0 && ft_strlen(strhold) < 1)
		{
			if (strhold)
				free(strhold);
			free(lstcur);
			return 0;
		}
		if (read_ret == 0)
		{
			*line = ft_strdup(strhold);
			strhold = ft_strchr(strhold, '\0');
			strhold++;
			lstcur->string = strhold;
			return 1;
		}

		else if (ft_strchr(strhold, '\n'))
		{
			*line = ft_striso(strhold, '\n');
			strhold = ft_strchr(strhold, '\n');
			strhold++;
			lstcur->string = strhold;
			return 1;
		}
	}
}


















		


