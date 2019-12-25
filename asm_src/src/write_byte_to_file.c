/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_byte_to_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 17:20:01 by swedde            #+#    #+#             */
/*   Updated: 2019/12/25 17:20:27 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		write_byte_to_file(t_all *gen, unsigned char c)
{
	if (write(gen->fd, &c, 1) == -1)
	{
		ft_putendl("Error: Failed to write to file");
		do_exit(NULL, gen);
	}
	return (1);
}
