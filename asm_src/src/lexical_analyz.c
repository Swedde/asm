/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyz.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 22:58:42 by swedde            #+#    #+#             */
/*   Updated: 2020/01/14 16:59:40 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_token_type(int i)
{
	if (i == NAME_TYPE)
		ft_putstr("NAME");
	else if (i == COMMENT_TYPE)
		ft_putstr("COMMENT");
	else if (i == NL_TYPE)
		ft_putstr("NEW LINE");
	else if (i == LABEL_TYPE)
		ft_putstr("LABEL");
	else if (i == DELIM_TYPE)
		ft_putstr("SEPARATOR");
	else if (i == OP_TYPE)
		ft_putstr("INSTRUCTION");
	else if (i == REG_ARG_TYPE)
		ft_putstr("REGISTER");
	else if (i == DIR_ARG_TYPE)
		ft_putstr("DIRECT ARG");
	else if (i == DIR_LABL_ARG_TYPE)
		ft_putstr("DIRECT LABEL");
	else if (i == IND_ARG_TYPE)
		ft_putstr("INDIRECT ARG");
	else if (i == IND_LABL_ARG_TYPE)
		ft_putstr("INDIRECT LABEL");
	else if (i == END_FILE)
		ft_putstr("END FILE");
}

t_token	*next_token(t_token *token, int i)
{
	while (i)
	{
		token = token->next;
		i--;
	}
	return (token);
}

void	print_expexted_exit(t_all *gen, t_token *token, int i, ...)
{
	va_list	ap;
	int		a;
	int		f;

	f = 0;
	va_start(ap, i);
	print_point(token->point);
	ft_putstr(": Lexical error: \"");
	token->type == NL_TYPE ? ft_putstr("NEW LINE") : ft_putstr(token->content);
	ft_putstr("\"\n\tToken type: ");
	print_token_type(token->type);
	ft_putstr("\n\tExpected type: ");
	while (i)
	{
		if (f)
			ft_putstr(" or ");
		a = va_arg(ap, int);
		print_token_type(a);
		f = 1;
		i--;
	}
	ft_putchar('\n');
	va_end(ap);
	do_exit(NULL, gen);
}

int		is_equal_token_type(t_token *token, int i, ...)
{
	int		a;
	va_list	ap;

	if (!token)
		return (0);
	va_start(ap, i);
	while (i)
	{
		a = va_arg(ap, int);
		if (token->type == a)
		{
			va_end(ap);
			return (1);
		}
		i--;
	}
	va_end(ap);
	return (0);
}

void	parse_live(t_all *gen, t_token *token)
{
	if (!is_equal_token_type(next_token(token, 1), 2, DIR_ARG_TYPE,
	DIR_LABL_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 1), 2, DIR_ARG_TYPE,
		DIR_LABL_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 2), 1, NL_TYPE))
		print_expexted_exit(gen, next_token(token, 2), 1, NL_TYPE);
	start_analyz(gen, next_token(token, 3));
}

void	parse_ld(t_all *gen, t_token *token)
{
	if (!is_equal_token_type(next_token(token, 1), 4, DIR_ARG_TYPE,
	DIR_LABL_ARG_TYPE, IND_ARG_TYPE, IND_LABL_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 1), 2, DIR_ARG_TYPE,
		IND_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 2), 1, DELIM_TYPE))
		print_expexted_exit(gen, next_token(token, 2), 1, DELIM_TYPE);
	if (!is_equal_token_type(next_token(token, 3), 1, REG_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 3), 1, REG_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 4), 1, NL_TYPE))
		print_expexted_exit(gen, next_token(token, 4), 1, NL_TYPE);
	start_analyz(gen, next_token(token, 5));
}

void	parse_st(t_all *gen, t_token *token)
{
	if (!is_equal_token_type(next_token(token, 1), 1, REG_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 1), 1, REG_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 2), 1, DELIM_TYPE))
		print_expexted_exit(gen, next_token(token, 2), 1, DELIM_TYPE);
	if (!is_equal_token_type(next_token(token, 3), 3, REG_ARG_TYPE,
	IND_ARG_TYPE, IND_LABL_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 3), 2, REG_ARG_TYPE,
		IND_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 4), 1, NL_TYPE))
		print_expexted_exit(gen, next_token(token, 4), 1, NL_TYPE);
	start_analyz(gen, next_token(token, 5));
}

void	parse_add(t_all *gen, t_token *token)
{
	if (!is_equal_token_type(next_token(token, 1), 1, REG_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 1), 1, REG_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 2), 1, DELIM_TYPE))
		print_expexted_exit(gen, next_token(token, 2), 1, DELIM_TYPE);
	if (!is_equal_token_type(next_token(token, 3), 1, REG_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 3), 1, REG_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 4), 1, DELIM_TYPE))
		print_expexted_exit(gen, next_token(token, 4), 1, DELIM_TYPE);
	if (!is_equal_token_type(next_token(token, 5), 1, REG_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 5), 1, REG_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 6), 1, NL_TYPE))
		print_expexted_exit(gen, next_token(token, 6), 1, NL_TYPE);
	start_analyz(gen, next_token(token, 7));
}

void	parse_and(t_all *gen, t_token *token)
{
	if (!is_equal_token_type(next_token(token, 1), 5, REG_ARG_TYPE,
	IND_ARG_TYPE, IND_LABL_ARG_TYPE, DIR_ARG_TYPE, DIR_LABL_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 1), 3, REG_ARG_TYPE,
		IND_ARG_TYPE, DIR_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 2), 1, DELIM_TYPE))
		print_expexted_exit(gen, next_token(token, 2), 1, DELIM_TYPE);
	if (!is_equal_token_type(next_token(token, 3), 5, REG_ARG_TYPE,
	IND_ARG_TYPE, IND_LABL_ARG_TYPE, DIR_ARG_TYPE, DIR_LABL_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 3), 3, REG_ARG_TYPE,
		IND_ARG_TYPE, DIR_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 4), 1, DELIM_TYPE))
		print_expexted_exit(gen, next_token(token, 4), 1, DELIM_TYPE);
	if (!is_equal_token_type(next_token(token, 5), 1, REG_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 5), 1, REG_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 6), 1, NL_TYPE))
		print_expexted_exit(gen, next_token(token, 6), 1, NL_TYPE);
	start_analyz(gen, next_token(token, 7));
}

void	parse_ldi(t_all *gen, t_token *token)
{
	if (!is_equal_token_type(next_token(token, 1), 5, REG_ARG_TYPE,
	IND_ARG_TYPE, IND_LABL_ARG_TYPE, DIR_ARG_TYPE, DIR_LABL_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 1), 3, REG_ARG_TYPE,
		IND_ARG_TYPE, DIR_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 2), 1, DELIM_TYPE))
		print_expexted_exit(gen, next_token(token, 2), 1, DELIM_TYPE);
	if (!is_equal_token_type(next_token(token, 3), 3, REG_ARG_TYPE,
	DIR_ARG_TYPE, DIR_LABL_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 3), 3, REG_ARG_TYPE,
		DIR_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 4), 1, DELIM_TYPE))
		print_expexted_exit(gen, next_token(token, 4), 1, DELIM_TYPE);
	if (!is_equal_token_type(next_token(token, 5), 1, REG_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 5), 1, REG_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 6), 1, NL_TYPE))
		print_expexted_exit(gen, next_token(token, 6), 1, NL_TYPE);
	start_analyz(gen, next_token(token, 7));
}

void	parse_sti(t_all *gen, t_token *token)
{
	if (!is_equal_token_type(next_token(token, 1), 1, REG_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 1), 1, REG_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 2), 1, DELIM_TYPE))
		print_expexted_exit(gen, next_token(token, 2), 1, DELIM_TYPE);
	if (!is_equal_token_type(next_token(token, 3), 5, REG_ARG_TYPE,
	IND_ARG_TYPE, IND_LABL_ARG_TYPE, DIR_ARG_TYPE, DIR_LABL_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 3), 3, REG_ARG_TYPE,
		IND_ARG_TYPE, DIR_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 4), 1, DELIM_TYPE))
		print_expexted_exit(gen, next_token(token, 4), 1, DELIM_TYPE);
	if (!is_equal_token_type(next_token(token, 5), 3, REG_ARG_TYPE,
	DIR_ARG_TYPE, DIR_LABL_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 5), 2, REG_ARG_TYPE,
		DIR_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 6), 1, NL_TYPE))
		print_expexted_exit(gen, next_token(token, 6), 1, NL_TYPE);
	start_analyz(gen, next_token(token, 7));
}

void	parse_aff(t_all *gen, t_token *token)
{
	if (!is_equal_token_type(next_token(token, 1), 1, REG_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 1), 1, REG_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 2), 1, NL_TYPE))
		print_expexted_exit(gen, next_token(token, 2), 1, NL_TYPE);
	start_analyz(gen, next_token(token, 3));
}

void	parse_op(t_all *gen, t_token *token)
{
	(!ft_strcmp(token->content, "live") ||
	!ft_strcmp(token->content, "fork") ||
	!ft_strcmp(token->content, "zjmp") ||
	!ft_strcmp(token->content, "lfork")) ?
		parse_live(gen, token) : 0;
	(!ft_strcmp(token->content, "ld") ||
	!ft_strcmp(token->content, "lld")) ?
		parse_ld(gen, token) : 0;
	!ft_strcmp(token->content, "st") ?
		parse_st(gen, token) : 0;
	(!ft_strcmp(token->content, "add") ||
	!ft_strcmp(token->content, "sub")) ?
		parse_add(gen, token) : 0;
	(!ft_strcmp(token->content, "and") ||
	!ft_strcmp(token->content, "or") ||
	!ft_strcmp(token->content, "xor")) ?
		parse_and(gen, token) : 0;
	(!ft_strcmp(token->content, "ldi") ||
	!ft_strcmp(token->content, "lldi")) ?
		parse_ldi(gen, token) : 0;
	!ft_strcmp(token->content, "sti") ?
		parse_sti(gen, token) : 0;
	!ft_strcmp(token->content, "aff") ?
		parse_aff(gen, token) : 0;
}

void	parse_name(t_all *gen, t_token *token)
{
	if (gen->name)
	{
		print_point(token->point);
		ft_putendl(": Lexical error:\n\tSecond name");
		do_exit(NULL, gen);
	}
	if (!is_equal_token_type(token->next, 1, NL_TYPE))
		print_expexted_exit(gen, token->next, 1, NL_TYPE);
	gen->name = 1;
	start_analyz(gen, next_token(token, 2));
}

void	parse_comment(t_all *gen, t_token *token)
{
	if (gen->comment)
	{
		print_point(token->point);
		ft_putendl(": Lexical error:\n\tSecond comment");
		do_exit(NULL, gen);
	}
	if (!is_equal_token_type(token->next, 1, NL_TYPE))
		print_expexted_exit(gen, token->next, 1, NL_TYPE);
	gen->comment = 1;
	start_analyz(gen, next_token(token, 2));
}

void	start_analyz(t_all *gen, t_token *token)
{
	if (!token || (gen->name && gen->comment && token->type == END_FILE))
		return ;
	if (token->type == NL_TYPE)
		start_analyz(gen, token->next);
	else if (token->type == NAME_TYPE)
		parse_name(gen, token);
	else if (token->type == COMMENT_TYPE)
		parse_comment(gen, token);
	else if (gen->name && gen->comment)
	{
		if (token->type == LABEL_TYPE)
			token->next->type != END_FILE ? start_analyz(gen, token->next)
			: print_expexted_exit(gen, token, 1, NL_TYPE);
		else if (token->type == OP_TYPE)
			parse_op(gen, token);
		else
			print_expexted_exit(gen, token, 2, LABEL_TYPE, OP_TYPE);
	}
	else if (gen->name)
		print_expexted_exit(gen, token, 1, COMMENT_TYPE);
	else if (gen->comment)
		print_expexted_exit(gen, token, 1, NAME_TYPE);
	else
		print_expexted_exit(gen, token, 2, NAME_TYPE, COMMENT_TYPE);
}

int		is_exist_label(t_token *token, char *s)
{
	while (token)
	{
		if (token->type == LABEL_TYPE && !ft_strcmp(token->content, s))
			return (1);
		token = token->next;
	}
	return (0);
}

void	print_nonexist_label_exit(t_all *gen, t_token *token)
{
	print_point(token->point);
	ft_putstr(": Lexical error:\n\tNonexistent label reference\n");
	do_exit(NULL, gen);
}

void	check_nonexist_labels(t_all *gen)
{
	t_token *token;

	token = gen->token;
	while (token)
	{
		if (token->type == IND_LABL_ARG_TYPE ||
		token->type == DIR_LABL_ARG_TYPE)
			if (!is_exist_label(gen->token, token->content))
				print_nonexist_label_exit(gen, token);
		token = token->next;
	}
}

void	lexical_analyz(t_all *gen)
{
	start_analyz(gen, gen->token);
	check_nonexist_labels(gen);
}
