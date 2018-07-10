/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhohls <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 12:21:45 by rhohls            #+#    #+#             */
/*   Updated: 2018/06/18 11:38:47 by rhohls           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

#include <stdio.h>

static char		*line_and_adjust_str(char *str, t_list *curr_node)
{
	int		i;
	int		len;
	char	*ret;
	char	*temp;

	i = 0;
	len = ft_strlen(str);
	while (str[i] && str[i] != '\n')
		i++;
	ret = ft_strsub(str, 0, i);
	//printf("stri %i, str i +1 %i\n",str[i],str[i+1]);
	if (!str[i] || (str[i] && !str[i + 1]))
	{
		//printf("deleteing\n");
		ft_strdel(&str);
		curr_node->STRING = str;
		return (ret);
	}
	temp = str;
	str = ft_strdup(str + i + 1);
	free(temp);
	curr_node->STRING = str;
	return(ret);
}

static t_list	*find_fd_str(const int fd, t_list **list)
{
	t_list	*curr_node;

	curr_node = *list;
	while (curr_node)
	{
		if ((int)curr_node->FD == fd)
			return (curr_node);
		curr_node = curr_node->next;
	}
	//printf("ADDED NEW NODE\n");
	curr_node = ft_lstnew(0, fd);
	curr_node->STRING = ft_strnew(1);
	curr_node->FD = fd;
	ft_lstadd(list, curr_node);
	return (curr_node);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*listhold;
	t_list			*curr_node;
	char			*str;
	int				read_ret;
	char			buffstr[BUFF_SIZE + 1];

	if (BUFF_SIZE <= 0 || !line || (fd < -1))
		return (-1);
	curr_node = find_fd_str(fd, &listhold);
	str = curr_node->STRING;
	//printf("current string |%s|\n", str);
	if (!str)
		str = ft_strnew(1);
	//printf("1\n");
	while(!(ft_strchr(str, '\n')))
	{
		read_ret = read(fd, buffstr, BUFF_SIZE);
		if (read_ret == -1)
			return (-1);
		buffstr[read_ret] = '\0';
		str = ft_strjoinfree(str, buffstr);
		if (read_ret == 0)
		{
			if (*str == '\0')
				return (0);
			break ;
		}
	}
	//printf("current string after read |%s| read re: %i\n", str, read_ret);
	//printf("2\n");
	//printf("address before 1--%p 2--%p\n", str, curr_node->STRING);
	*line = line_and_adjust_str(str, curr_node);
	//printf("address after 1--%p 2--%p\n", str, curr_node->STRING);
//	curr_node->STRING = str;
	//printf("string that got stored |%s|\n", curr_node->STRING);
	return (1);
}
