/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 17:41:33 by swedde            #+#    #+#             */
/*   Updated: 2019/12/19 17:24:41 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "get_next_line.h"
# include "op.h"
# include <stdarg.h>

# define NAME_TYPE 1
# define COMMENT_TYPE 2
# define NL_TYPE 3
# define LABEL_TYPE 4
# define DELIM_TYPE 5
# define OP_TYPE 6
# define REG_ARG_TYPE 7
# define DIR_ARG_TYPE 8
# define DIR_LABL_ARG_TYPE 9
# define IND_ARG_TYPE 10
# define IND_LABL_ARG_TYPE 11
# define END_FILE 12

typedef struct	s_op
{
	char	*name;
	int		len;
	int		*arg;
	int		op_code;
	int		vm1;
	char	*discraibe;
	int		arg_code;
	int		carry;
}				t_op;
/*
static t_op		g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};
*/
typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct	s_token
{
	int				type;
	char*			content;
	t_point			point;
	int				size;
	unsigned char	op_code;
	unsigned char	arg_code;
	int				dir_size;
	struct s_token	*next;
}				t_token;

typedef union	u_test
{
	unsigned		a;
	struct
	{
		unsigned char	c1:8;
		unsigned char	c2:8;
		unsigned char	c3:8;
		unsigned char	c4:8;
	}				ch;
}				uni_t;

typedef union	u_short
{
	unsigned short	a;
	struct
	{
		unsigned char	c1:8;
		unsigned char	c2:8;
	}ch;
}				t_short;

typedef struct	s_all
{
	int			i;
	char		*file;
	t_point		point;
	t_token		*token;
	int			fd;
	int			fd_s;
	char		*file_name;
	char		*error;
	int			name;
	int			comment;
	int			size;
	int			op_size;
}				t_all;

t_all			*set_def_gen(char *s);
int				write_int_to_file(t_all	*gen, int to_file);
void			do_exit(char **error_mes, t_all *gen);
int				reading(t_all *gen);
char			*char_to_string(char c);
t_token			*new_token(int type, char *content, t_point point);
void			push_tail_token(t_token **head, int type, char *con,
				t_point point);
void			lst_del_token(t_token *token);
void			print_point(t_point a);
void			lexical_analyz(t_all *gen);
void			print_token(t_token *token);
void			start_analyz(t_all *gen, t_token *token);
void			recording(t_all *gen);
void			set_size_code(t_all *gen, t_token *token);
int				write_short_to_file(t_all *gen, short to_file);
t_token			*next_token(t_token *token, int i);

#endif
