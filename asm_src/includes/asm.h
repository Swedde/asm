/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 17:41:33 by swedde            #+#    #+#             */
/*   Updated: 2019/12/12 17:34:33 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

#include "libft.h"
#include "get_next_line.h"
#include "op.h"

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;


typedef struct	s_token
{
    char*		type;
	char*		content;
	t_point		point;
}				t_token;

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
    int			fd;
    int			fd_s;
    char*		name;
    char*		comment;
	char*		file_name;
	char*		error;
	t_token*	token;
	char*		file;
}				t_all;

t_all*			set_def_gen(char *s);
int				get_name_and_comment(t_all* gen);
int             write_int_to_file(t_all* gen, int to_file);
void    		do_exit(char**   error_mes, t_all*   gen);
int	    		reading(t_all*	gen);


#endif