/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:48:57 by swedde            #+#    #+#             */
/*   Updated: 2019/12/26 15:44:49 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int     main(int ac, char **av)
{
	t_all*		gen;

	if (ac == 1)
	{
		ft_putstr("Usage: ");
		ft_putstr(av[0]);
		ft_putstr(" <sourcefile.s> \n");
		exit(-1);
	}
	gen = set_def_gen(av[ac-1]);
	reading(gen);
//	print_token(gen->token);
	lexical_analyz(gen);
	recording(gen);
	do_exit(NULL, gen);
    return (0);
}
