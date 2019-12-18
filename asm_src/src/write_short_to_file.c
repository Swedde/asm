/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_short_to_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 01:39:31 by swedde            #+#    #+#             */
/*   Updated: 2019/12/18 01:43:18 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	write_short_to_file_helper(int fd, t_short a)
{
	unsigned char	c;

	c = a.ch.c2;
	write(fd, &c, 1);
	c = a.ch.c1;
	write(fd, &c, 1);
	return (0);
}

int         write_short_to_file(t_all* gen, short to_file)
{
    t_short	uni_z;

	uni_z.a = to_file;
	return (write_short_to_file_helper(gen->fd, uni_z));
}
