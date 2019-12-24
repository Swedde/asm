/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 17:41:33 by swedde            #+#    #+#             */
/*   Updated: 2019/12/24 14:45:47 by nsheev           ###   ########.fr       */
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
