/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 17:41:33 by swedde            #+#    #+#             */
/*   Updated: 2019/12/12 02:01:38 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include "libft.h"
#include "get_next_line.h"
#include "op.h"

typedef union	u_test
{
    unsigned a;
    struct{
    unsigned char c1:8;
    unsigned char c2:8;
    unsigned char c3:8;
    unsigned char c4:8;
    }ch;
}				uni_t;

typedef struct  s_all
{
    int		fd;
    int		fd_s;
    char*	name;
    char*	comment;
	char*	file_name;
    int     fatal;
}				t_all;

char*			get_file_name(char *s);
int				get_name_and_comment(t_all* gen);
int             write_int_to_file(t_all* gen, int to_file);


#endif