/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_int_to_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 02:00:29 by swedde            #+#    #+#             */
/*   Updated: 2020/01/14 17:10:15 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	write_int_to_file_helper(int fd, union u_int a)
{
	unsigned char	c;

	c = a.t_ch.c4;
	write(fd, &c, 1);
	c = a.t_ch.c3;
	write(fd, &c, 1);
	c = a.t_ch.c2;
	write(fd, &c, 1);
	c = a.t_ch.c1;
	write(fd, &c, 1);
	return (0);
}

int			write_int_to_file(t_all *gen, int to_file)
{
	union u_int	uni_z;

	uni_z.a = to_file;
	return (write_int_to_file_helper(gen->fd, uni_z));
}
