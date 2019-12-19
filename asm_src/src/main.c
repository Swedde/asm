/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:48:57 by swedde            #+#    #+#             */
/*   Updated: 2019/12/19 17:29:55 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int     main(int ac, char **av)
{
	t_all*		gen;

	if (ac == 1)
	{
		ft_putendl("Usage: ../resourses/asm [-a] <sourcefile.s> \n\t-a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output");
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
