/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 14:48:51 by swedde            #+#    #+#             */
/*   Updated: 2019/12/11 19:37:57 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 4

# include <stdlib.h>

# include <string.h>

# include <unistd.h>

# include <stdio.h>

# include <fcntl.h>

typedef struct		s_g_list
{
	char			*content;
	int				sfd;
	struct s_g_list	*next;
}					t_g_list;

int					get_next_line(const int fd, char **line);

#endif
