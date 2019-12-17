/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:48:57 by swedde            #+#    #+#             */
/*   Updated: 2019/12/17 21:39:44 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int     main(int ac, char **av)
{
	t_all*		gen;

	if (ac == 1)
	{
		ft_putendl("No arguments");
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
