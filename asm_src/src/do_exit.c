/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 13:40:41 by nsheev            #+#    #+#             */
/*   Updated: 2019/12/14 23:39:52 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void    do_exit(char**   error_mes, t_all*   gen)
{
    if (error_mes)
    {
        ft_putendl(*error_mes);
    	ft_strdel(error_mes);
	}
    ft_strdel(&gen->file_name);
	lst_del_token(gen->token);
    ft_strdel(&gen->file);
    free(gen);
	exit(-1);
}