/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_int_to_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 02:00:29 by swedde            #+#    #+#             */
/*   Updated: 2019/12/26 18:55:19 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	write_int_to_file_helper(int fd, uni_t a)
{
	unsigned char	c;

	c = a.ch.c4;
	write(fd, &c, 1);
	c = a.ch.c3;
	write(fd, &c, 1);
	c = a.ch.c2;
	write(fd, &c, 1);
	c = a.ch.c1;
	write(fd, &c, 1);
	return (0);
}

int			write_int_to_file(t_all *gen, int to_file)
{
	uni_t	uni_z;

	uni_z.a = to_file;
	return (write_int_to_file_helper(gen->fd, uni_z));
}
