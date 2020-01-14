/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_short_to_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 01:39:31 by swedde            #+#    #+#             */
/*   Updated: 2020/01/14 17:12:54 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	write_short_to_file_helper(int fd, t_short a)
{
	unsigned char	c;

	c = a.t_sch.c2;
	write(fd, &c, 1);
	c = a.t_sch.c1;
	write(fd, &c, 1);
	return (0);
}

int			write_short_to_file(t_all *gen, short to_file)
{
	t_short uni_z;

	uni_z.a = to_file;
	return (write_short_to_file_helper(gen->fd, uni_z));
}
