/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recording.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 00:11:50 by swedde            #+#    #+#             */
/*   Updated: 2019/12/17 21:58:36 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

typedef struct	s_string
{
	int		len;
	char*	s;
}				t_string;

void	write_byte_to_file(t_all* gen, unsigned char c)
{
	write(gen->fd, &c, 1);
}

int		write_string_to_file(int fd, char*	s,	int len)
{
	int				i;
	unsigned char	c;

	i = 0;
	while (s[i])
	{
		c = s[i];
		write(fd, &c, 1);
		i++;
	}
	c = 0;
	while (i < len)
	{
		write(fd, &c, 1);
		i++;
	}
	return (0);
}

int		write_nam_com_to_file(t_all* gen, int len, int type)
{
	t_token*	token;

	token = gen->token;
	while (token->type != type)
		token = token->next;
	if (ft_strlen(token->content) > len)
	{
		print_point(token->point);
		ft_putstr(": Constant error:\n\t");
		print_token(token);
		ft_putendl(" is too long");
		do_exit(NULL, gen);
	}
	write_string_to_file(gen->fd, token->content, len);
	write_int_to_file(gen, 0);
}

void		parse_op_t_dir(t_all* gen, t_token* token, int dir_size, char op_c)
{
	token->op_code = op_c;
	token->arg_code = 0;
	token->next->size = gen->size;
	gen->size += dir_size;
	token->next->dir_size = dir_size;
	set_size_code(gen, next_token(token, 3));
}

void		parse_op_11_sti(t_all* gen, t_token* token)
{
	unsigned char	arg_1;
	unsigned char	arg_2;
	unsigned char	arg_3;
	t_token*		tmp;

	token->op_code = (char)11;
	arg_1 = T_REG << 6;
	if ((tmp = next_token(token, 3))->type == REG_ARG_TYPE)
	{
		tmp->size = gen->size++;
		arg_2 = T_REG << 4;
	}
	else if (tmp->type == DIR_ARG_TYPE || tmp->type == DIR_LABL_ARG_TYPE)
	{
		tmp->size = gen->size;
		tmp->dir_size = 2;
		gen->size += 2;
		arg_2 = 2 << 4;
	}
	else
	{
		tmp->size = gen->size;
		gen->size += 2;
		arg_2 = 3 << 4;
	}
	if ((tmp = next_token(token, 5))->type == REG_ARG_TYPE)
	{
		tmp->size = gen->size++;
		arg_3 = T_REG << 2;
	}
	else
	{
		tmp->size = gen->size;
		tmp->dir_size = 2;
		gen->size += 2;
		arg_3 = 2 << 2;
	}
	token->arg_code = arg_1 | arg_2 | arg_3;
	gen->size++;
	set_size_code(gen, next_token(token, 7));
}

void		get_op_code(t_all* gen, t_token* token)
{
	if (!ft_strcmp(token->content, "live"))
		parse_op_t_dir(gen, token, 4, 1);
/*	else if (!ft_strcmp(token->content, "ld"))
		op_code = 2;
	else if (!ft_strcmp(token->content, "st"))
		op_code = 3;
	else if (!ft_strcmp(token->content, "add"))
		op_code = 4;
	else if (!ft_strcmp(token->content, "sub"))
		op_code = 5;
	else if (!ft_strcmp(token->content, "and"))
		op_code = 6;
	else if (!ft_strcmp(token->content, "or"))
		op_code = 7;
	else if (!ft_strcmp(token->content, "xor"))
		op_code = 8;*/
	else if (!ft_strcmp(token->content, "zjmp"))
		parse_op_t_dir(gen, token, 2, 9);
/*	else if (!ft_strcmp(token->content, "ldi"))
		op_code = 10;*/
	else if (!ft_strcmp(token->content, "sti"))
		parse_op_11_sti(gen, token);
/* 	else if (!ft_strcmp(token->content, "fork"))
		op_code = 12;
	else if (!ft_strcmp(token->content, "lld"))
		op_code = 13;
	else if (!ft_strcmp(token->content, "lldi"))
		op_code = 14;
	else if (!ft_strcmp(token->content, "lfork"))
		op_code = 15;
	else if (!ft_strcmp(token->content, "aff"))
		op_code = 16;*/
}

void		set_op_size(t_all* gen, t_token* token)
{
	token->size = gen->size;
	gen->size++;
	get_op_code(gen, token);
}

void		set_size_code(t_all* gen, t_token* token)
{
	if (token->type == END_FILE)
		return ;
	else if (token->type == NL_TYPE || token->type == NAME_TYPE || token->type == COMMENT_TYPE)
	{
		token->size = 0;
		set_size_code(gen, token->next);
	}
	else if (token->type == LABEL_TYPE)
	{
		token->size = gen->size;
		set_size_code(gen, token->next);
	}
	else if (token->type == OP_TYPE)
		set_op_size(gen, token);
	else
		set_size_code(gen, token->next);
}

void		recording(t_all* gen)
{
	if ((gen->fd = open(gen->file_name, O_RDWR|O_CREAT|O_TRUNC, 0777)) == -1)
	{
		ft_putstr("Error: Failed to create file\n");
		do_exit(NULL, gen);
	}
	write_int_to_file(gen, COREWAR_EXEC_MAGIC);
	write_nam_com_to_file(gen, PROG_NAME_LENGTH, NAME_TYPE);
	write_int_to_file(gen, CHAMP_MAX_SIZE);
	write_nam_com_to_file(gen, COMMENT_LENGTH, COMMENT_TYPE);
	set_size_code(gen, gen->token);
//	write_code_to_file(gen);
	ft_putendl("Succefull record");
    close(gen->fd);
}
