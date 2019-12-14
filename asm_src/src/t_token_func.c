/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 00:46:14 by swedde            #+#    #+#             */
/*   Updated: 2019/12/13 19:30:05 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token*	new_token(int type, char* content, t_point point)
{
	t_token*	new;

	new = (t_token*)malloc(sizeof(t_token));
	new->type = type;
	new->content = ft_strdup(content);
	new->point.x = point.x;
	new->point.y = point.y;
	new->next = NULL;
	return (new);
}

void		push_tail_token(t_token** head, int type, char* con, t_point point)
{
	t_token*	tmp;

	if (!*head)
		*head = new_token(type, con, point);
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token(type, con, point);
	}
}

void		lst_del_token(t_token* token)
{
	t_token*	tmp;

	tmp = token;
	while (token)
	{
		token = token->next;
		free(tmp->content);
		free(tmp);
		tmp = token;
	}
}

void		print_token(t_token*	token)
{
	while (token)
	{
		printf("{ %d }%s", token->type, token->content);
		token = token->next;
	}
}