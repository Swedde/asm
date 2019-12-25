/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recording.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 00:11:50 by swedde            #+#    #+#             */
/*   Updated: 2019/12/25 18:33:10 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		set_arg_and_size(t_all *gen, t_token *tmp, int move, int dir_size)
{
	int		arg;

	arg = 0;
	if (tmp->type == REG_ARG_TYPE)
	{
		arg = 1;
		gen->size++;
	}
	else if (tmp->type == DIR_ARG_TYPE || tmp->type == DIR_LABL_ARG_TYPE)
	{
		tmp->size = gen->op_size;
		tmp->dir_size = dir_size;
		gen->size += dir_size;
		arg = 2;
	}
	else
	{
		tmp->size = gen->op_size;
		gen->size += 2;
		arg = 3;
	}
	return (arg << move);
}

int		op_dir(t_all *gen, t_token *token, char op_c, int dir_size)
{
	token->op_code = op_c;
	token->arg_code = 0;
	gen->size += dir_size;
	token->next->dir_size = dir_size;
	token->next->size = gen->op_size;
	set_size_code(gen, next_token(token, 3));
	return (0);
}

int		op_dirind_reg(t_all *gen, t_token *token, char op_c, int dir_size)
{
	unsigned char	arg_1;
	unsigned char	arg_2;

	gen->size++;
	token->op_code = op_c;
	arg_1 = set_arg_and_size(gen, next_token(token, 1), 6, dir_size);
	arg_2 = set_arg_and_size(gen, next_token(token, 3), 4, dir_size);
	token->arg_code = arg_1 | arg_2;
	set_size_code(gen, next_token(token, 5));
	return (0);
}

int		op_reg_regdirind_regdir(
	t_all *gen, t_token *token, char op_c, int dir_size)
{
	unsigned char	arg_1;
	unsigned char	arg_2;
	unsigned char	arg_3;

	gen->size++;
	token->op_code = op_c;
	arg_1 = set_arg_and_size(gen, next_token(token, 1), 6, dir_size);
	arg_2 = set_arg_and_size(gen, next_token(token, 3), 4, dir_size);
	arg_3 = set_arg_and_size(gen, next_token(token, 5), 2, dir_size);
	token->arg_code = arg_1 | arg_2 | arg_3;
	set_size_code(gen, next_token(token, 7));
	return (0);
}

int		op_reg_regind(t_all *gen, t_token *token, char op_c)
{
	unsigned char	arg_1;
	unsigned char	arg_2;

	gen->size++;
	token->op_code = op_c;
	arg_1 = set_arg_and_size(gen, next_token(token, 1), 6, 0);
	arg_2 = set_arg_and_size(gen, next_token(token, 3), 4, 0);
	token->arg_code = arg_1 | arg_2;
	set_size_code(gen, next_token(token, 5));
	return (0);
}

int		op_reg_reg_reg(t_all *gen, t_token *token, char op_c)
{
	token->op_code = op_c;
	gen->size += 4;
	token->arg_code = (1 << 6) | (1 << 4) | (1 << 2);
	set_size_code(gen, next_token(token, 7));
	return (0);
}

int		op_regdirind_regdirind_reg(
	t_all *gen, t_token *token, char op_c, int dir_size)
{
	unsigned char	arg_1;
	unsigned char	arg_2;
	unsigned char	arg_3;

	gen->size++;
	token->op_code = op_c;
	arg_1 = set_arg_and_size(gen, next_token(token, 1), 6, dir_size);
	arg_2 = set_arg_and_size(gen, next_token(token, 3), 4, dir_size);
	arg_3 = set_arg_and_size(gen, next_token(token, 5), 2, dir_size);
	token->arg_code = arg_1 | arg_2 | arg_3;
	set_size_code(gen, next_token(token, 7));
	return (0);
}

int		op_regdirind_regdir_reg(
	t_all *gen, t_token *token, char op_c, int dir_size)
{
	unsigned char	arg_1;
	unsigned char	arg_2;
	unsigned char	arg_3;

	gen->size++;
	token->op_code = op_c;
	arg_1 = set_arg_and_size(gen, next_token(token, 1), 6, dir_size);
	arg_2 = set_arg_and_size(gen, next_token(token, 3), 4, dir_size);
	arg_3 = set_arg_and_size(gen, next_token(token, 5), 2, dir_size);
	token->arg_code = arg_1 | arg_2 | arg_3;
	set_size_code(gen, next_token(token, 7));
	return (0);
}

int		op_reg(t_all *gen, t_token *token, char op_c)
{
	gen->size += 2;
	token->op_code = op_c;
	token->arg_code = 1 << 6;
	set_size_code(gen, next_token(token, 3));
	return (0);
}

void	get_op_code(t_all *gen, t_token *token)
{
	!ft_strcmp(token->content, "live") ? op_dir(gen, token, 1, 4) : 0;
	!ft_strcmp(token->content, "ld") ? op_dirind_reg(gen, token, 2, 4) : 0;
	!ft_strcmp(token->content, "st") ? op_reg_regind(gen, token, 3) : 0;
	!ft_strcmp(token->content, "add") ? op_reg_reg_reg(gen, token, 4) : 0;
	!ft_strcmp(token->content, "sub") ? op_reg_reg_reg(gen, token, 5) : 0;
	!ft_strcmp(token->content, "and") ?
		op_regdirind_regdirind_reg(gen, token, 6, 4) : 0;
	!ft_strcmp(token->content, "or") ?
		op_regdirind_regdirind_reg(gen, token, 7, 4) : 0;
	!ft_strcmp(token->content, "xor") ?
		op_regdirind_regdirind_reg(gen, token, 8, 4) : 0;
	!ft_strcmp(token->content, "zjmp") ? op_dir(gen, token, 9, 2) : 0;
	!ft_strcmp(token->content, "ldi") ?
		op_regdirind_regdir_reg(gen, token, 10, 2) : 0;
	!ft_strcmp(token->content, "sti") ?
		op_reg_regdirind_regdir(gen, token, 11, 2) : 0;
 	!ft_strcmp(token->content, "fork") ? op_dir(gen, token, 12, 2) : 0;
	!ft_strcmp(token->content, "lld") ? op_dirind_reg(gen, token, 13, 4) : 0;
	!ft_strcmp(token->content, "lldi") ?
		op_regdirind_regdir_reg(gen, token, 14, 2) : 0;
	!ft_strcmp(token->content, "lfork") ? op_dir(gen, token, 15, 2) : 0;
	!ft_strcmp(token->content, "aff") ? op_reg(gen, token, 16) : 0;
}

int		set_op_size(t_all *gen, t_token *token)
{
	token->size = gen->size;
	gen->op_size = gen->size;
	gen->size++;
	get_op_code(gen, token);
	return (0);
}

void	set_size_code(t_all *gen, t_token *token)
{
	if (token->type == END_FILE)
		return ;
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

int		get_label_value(t_token *start, t_token *token)
{
	while (start)
	{
		if (start->type == LABEL_TYPE &&
		!ft_strcmp(start->content, token->content))
			return (start->size - token->size);
		start = start->next;
	}
	return (0);
}

void	write_exec_code_to_file(t_all *gen, t_token *token)
{
	while (token)
	{
		if (token->type == OP_TYPE && write_byte_to_file(gen, token->op_code))
			token->arg_code ? write_byte_to_file(gen, token->arg_code) : 0;
		else if (token->type == REG_ARG_TYPE)
			write_byte_to_file(gen, (unsigned char)ft_atoi(token->content));
		else if (token->type == DIR_ARG_TYPE)
			if (token->dir_size == 2)
				write_short_to_file(gen, (short)ft_atoi(token->content));
			else
				write_int_to_file(gen, ft_atoi(token->content));
		else if (token->type == DIR_LABL_ARG_TYPE)
			if (token->dir_size == 2)
				write_short_to_file(gen,
				(short)get_label_value(gen->token, token));
			else
				write_int_to_file(gen, get_label_value(gen->token, token));
		else if (token->type == IND_ARG_TYPE)
			write_short_to_file(gen, (short)ft_atoi(token->content));
		else if (token->type == IND_LABL_ARG_TYPE)
			write_short_to_file(gen, get_label_value(gen->token, token));
		token = token->next;
	}
}

void	recording(t_all *gen)
{
	if ((gen->fd = open(gen->file_name, O_RDWR|O_CREAT|O_TRUNC, 0777)) == -1)
	{
		ft_putendl("Error: Failed to create file");
		do_exit(NULL, gen);
	}
	set_size_code(gen, gen->token);
	write_int_to_file(gen, COREWAR_EXEC_MAGIC);
	write_nam_com_to_file(gen, PROG_NAME_LENGTH, NAME_TYPE);
	write_int_to_file(gen, gen->size);
	write_nam_com_to_file(gen, COMMENT_LENGTH, COMMENT_TYPE);
	write_exec_code_to_file(gen, gen->token);
	ft_putstr("Writing output program to ");
	ft_putendl(gen->file_name);
    close(gen->fd);
}
