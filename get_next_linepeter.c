/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppreez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 11:25:43 by ppreez            #+#    #+#             */
/*   Updated: 2018/06/18 11:48:21 by ppreez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_strjoinfree(void *s1, char const *s2)
{
	char *temp;

	temp = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	s1 = temp;
	return (s1);
}

int				assign_pt2(int i, char **line, t_list *node, char *buffer)
{
	char *str;

	str = (char *)node->content;
	if (!(read(node->content_size, buffer, BUFF_SIZE)))
	{
		if (i == 0)
			return (0);
		else
		{
			free(*line);
			*line = ft_strdup(node->content);
			ft_strclr(str);
			return (1);
		}
	}
	node->content = ft_strjoinfree(node->content, buffer);
	assign(line, node, buffer);
	return (1);
}

int				assign(char **line, t_list *node, char *buffer)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	str = (char *)node->content;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
	{
		if (i > 0)
		{
			free(*line);
			*line = ft_strsub(node->content, 0, i);
		}
		tmp = ft_strsub(node->content, i + 1, ft_strlen(str));
		free(node->content);
		node->content = tmp;
		return (1);
	}
	ft_bzero(buffer, BUFF_SIZE + 1);
	if (str[i] == '\0')
		i = assign_pt2(i, line, node, buffer);
	return (i);
}

static t_list	*read_list(const int fd, t_list **node)
{
	t_list *temp;

	temp = *node;
	while (temp)
	{
		if ((int)temp->content_size == fd)
			return (temp);
		temp = temp->next;
	}
	temp = ft_lstnew(0, fd);
	ft_lstadd(node, temp);
	return (temp);
}

int				get_next_line(const int fd, char **line)
{
	int				read_val;
	char			buffer[BUFF_SIZE + 1];
	static t_list	*head;
	t_list			*node;

	if (fd < 0 || !line)
		return (-1);
	*line = ft_strnew(0);
	ft_bzero(buffer, BUFF_SIZE + 1);
	node = read_list(fd, &head);
	if (node->content == NULL)
	{
		read_val = read(fd, buffer, BUFF_SIZE);
		if (read_val <= 0)
			return (read_val);
		if (!(node->content = (void*)ft_memalloc(BUFF_SIZE + 1)))
			return (-1);
		ft_memmove(node->content, buffer, BUFF_SIZE);
		node->content_size = fd;
	}
	read_val = assign(line, node, buffer);
	return (read_val);
}
