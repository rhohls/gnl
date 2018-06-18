/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhohls <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 12:21:45 by rhohls            #+#    #+#             */
/*   Updated: 2018/06/18 10:36:29 by rhohls           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

#include <stdio.h>

/*
** str iso: returns new string from str until char c
** then removes that from original using memmove
** BASICALLY str sub without malloc
*/

static char			*ft_striso(char *str, char c)
{
	size_t			i;
	size_t			len;
	size_t			leni;
	char			*ret;

	len = ft_strlen(str);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	ret = ft_strsub(str, 0, i);
	if (c == '\0')
		i--;
	leni = len - i;
	ft_memmove(str, (str + (i + 1)), leni);
	ft_bzero((str + leni), i);
	return (ret);
}

static t_gnl		*ft_lstnew_gnl(int fd)
{
	t_gnl			*new;

	if (!(new = (t_gnl*)ft_memalloc(sizeof(t_gnl))))
		return (NULL);
	new->string = ft_memalloc(1);
	new->fd = fd;
	return (new);
}

t_gnl				*find_fd(t_gnl **listhold, int fd, t_gnl *lstcur)
{
	t_gnl			*start;

	start = *listhold;
	while (*listhold)
	{
		if ((*listhold)->fd == fd)
		{
			lstcur = *listhold;
			break ;
		}
		if ((*listhold)->next)
			*listhold = (*listhold)->next;
		else
			break ;
	}
	if (!lstcur)
	{
		lstcur = ft_lstnew_gnl(fd);
		if (!(*listhold))
			*listhold = lstcur;
		else
			(*listhold)->next = lstcur;
	}
	*listhold = (start != NULL) ? start : *listhold;
	return (lstcur);
}

int					gnl_ret(t_gnl *lstcur, char **line, int fd, char *strhold)
{
	char			buffstr[BUFF_SIZE + 1];
	int				read_ret;
	char			c;

	while (TRUE)
	{
		ft_bzero(buffstr, (size_t)(BUFF_SIZE + 1));
		if ((read_ret = read(fd, buffstr, BUFF_SIZE)) == -1)
			return (-1);
		strhold = ft_strjoinfree(strhold, buffstr);
		if (read_ret == 0 && ft_strlen(strhold) == 0)
		{
			*line = ft_strdup("\0");
			return (0);
		}
		if (read_ret == 0 || ft_strchr(strhold, '\n'))
		{
			c = (read_ret == 0) ? '\0' : '\n';
			*line = ft_striso(strhold, c);
			lstcur->string = strhold;
			return (1);
		}
	}
}

int					get_next_line(const int fd, char **line)
{
	static t_gnl	*listhold;
	t_gnl			*lstcur;
	char			*strhold;

	if (BUFF_SIZE <= 0 || !line || (fd < -1))
		return (-1);
	lstcur = NULL;
	lstcur = find_fd(&listhold, fd, lstcur);
	strhold = lstcur->string;
	if (strhold && ft_strchr(strhold, '\n'))
	{
		*line = ft_striso(strhold, '\n');
		lstcur->string = strhold;
		return (1);
	}
	return (gnl_ret(lstcur, line, fd, strhold));
}
