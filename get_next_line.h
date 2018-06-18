/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhohls <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 07:19:30 by rhohls            #+#    #+#             */
/*   Updated: 2018/06/18 10:37:14 by rhohls           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "./libft/libft.h"

# define BUFF_SIZE 500
# define FD content_size
# define STRING content
# define TRUE 1
# define FALSE 0

int					get_next_line(const int fd, char **line);

typedef struct		s_gnl
{
	char			*string;
	int				fd;
	struct s_gnl	*next;
}					t_gnl;
#endif
