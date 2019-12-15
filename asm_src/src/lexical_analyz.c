/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyz.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 22:58:42 by swedde            #+#    #+#             */
/*   Updated: 2019/12/16 02:36:34 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		print_token_type(int i)
{
	if (i == 1)
		ft_putstr("NAME");
	if (i == 2)
		ft_putstr("COMMENT");
	if (i == 3)
		ft_putstr("NEW LINE");
	if (i == 4)
		ft_putstr("LABEL");
	if (i == 5)
		ft_putstr("SEPARATOR");
	if (i == 6)
		ft_putstr("INSTRUCTION");
	if (i == 7)
		ft_putstr("REGISTER");
	if (i == 8)
		ft_putstr("DIRECT ARG");
	if (i == 9)
		ft_putstr("DIRECT LABEL");
	if (i == 10)
		ft_putstr("INDIRECT ARG");
	if (i == 11)
		ft_putstr("INDIRECT LABEL");
	if (i == 12)
		ft_putstr("END FILE");
}

t_token*	next_token(t_token* token, int i)
{
	while (i)
	{
		token = token->next;
		i--;
	}
	return (token);
}

void		print_expexted_exit(t_all* gen, t_token* token, int i, ...)
{
	va_list	ap;
	int		a;
	int		f;

	f = 0;
	va_start(ap, i);
	print_point(token->point);
	ft_putstr(": Lexical error: \"");
	if (token->type == NL_TYPE)
		ft_putstr("\\n");
	else
		ft_putstr(token->content);
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

int			is_equal_token_type(t_token* token, int i, ...)
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
			return (1);
		i--;
	}
	va_end(ap);
	return (0);
}

void		parse_live(t_all* gen, t_token* token)
{
	if (!is_equal_token_type(next_token(token, 1), 1, DIR_ARG_TYPE))
		print_expexted_exit(gen, next_token(token, 1), 1, DIR_ARG_TYPE);
	if (!is_equal_token_type(next_token(token, 2), 1, NL_TYPE))
		print_expexted_exit(gen, next_token(token, 2), 1, NL_TYPE);
	start_analyz(gen, next_token(token, 3));
}

void		parse_op(t_all* gen, t_token* token)
{
	if (!ft_strcmp(token->content, "live"))
		parse_live(gen, token);
/*	else if (!ft_strcmp(token->content, "ld"))
		parse_ld(gen, token);
	else if (!ft_strcmp(token->content, "st"))
		parse_st(gen, token);
	else if (!ft_strcmp(token->content, "add"))
		parse_add(gen, token);
	else if (!ft_strcmp(token->content, "sub"))
		parse_sub(gen, token);
	else if (!ft_strcmp(token->content, "and"))
		parse_and(gen, token);
	else if (!ft_strcmp(token->content, "or"))
		parse_or(gen, token);
	else if (!ft_strcmp(token->content, "xor"))
		parse_xor(gen, token);
	else if (!ft_strcmp(token->content, "zjmp"))
		parse_zjmp(gen, token);
	else if (!ft_strcmp(token->content, "ldi"))
		parse_ldi(gen, token);
	else if (!ft_strcmp(token->content, "sti"))
		parse_sti(gen, token);
	else if (!ft_strcmp(token->content, "fork"))
		parse_fork(gen, token);
	else if (!ft_strcmp(token->content, "lld"))
		parse_lld(gen, token);
	else if (!ft_strcmp(token->content, "lldi"))
		parse_lldi(gen, token);
	else if (!ft_strcmp(token->content, "lfork"))
		parse_lfork(gen, token);
	else if (!ft_strcmp(token->content, "aff"))
		parse_aff(gen, token);*/
}

void		start_analyz(t_all*	gen, t_token* token)
{
	char*	error;

	if (!token)
		return ;
	if (token->type == NL_TYPE || token->type == END_FILE)
		start_analyz(gen, token->next);
	else if (token->type == NAME_TYPE)
	{
		if (gen->name)
		{
			print_point(token->point);
			ft_putendl(": Lexical error:\n\tSecond name");
			do_exit(NULL, gen);
		}
		gen->name = 1;
		start_analyz(gen, token->next);
	}
	else if (token->type == COMMENT_TYPE)
	{
		if (gen->comment)
		{
			print_point(token->point);
			ft_putendl(": Lexical error:\n\tSecond comment");
			do_exit(NULL, gen);
		}
		gen->comment = 1;
		start_analyz(gen, token->next);
	}
	else if (gen->name && gen->comment)
	{
		if (token->type == LABEL_TYPE)
			start_analyz(gen, token->next);
		else if (token->type == OP_TYPE)
			parse_op(gen, token);
		else
		{
			print_point(token->point);
			ft_putendl(": Lexical error:\n\tMust be label or instruction");
			do_exit(NULL, gen);
		}
	}
	else
	{
		print_point(token->point);
		ft_putendl(": Lexical error: Name and comment must be at the top of the file");
	}
}

void		lexical_analyz(t_all*	gen)
{
	if (!gen->token)
	{
		ft_putendl("Empty file");
		do_exit(NULL, gen);
	}
	start_analyz(gen, gen->token);
}
