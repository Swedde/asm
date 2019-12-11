/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 17:16:13 by nsheev            #+#    #+#             */
/*   Updated: 2019/09/16 19:15:01 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_delete(t_list **l)
{
	t_list	*buff;

	while (*l != NULL)
	{
		buff = *l;
		*l = (*l)->next;
		ft_memdel(&(buff->content));
		free(buff);
		buff = NULL;
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*l;
	t_list	*buff;

	if (!lst)
		return (NULL);
	if (!(l = f(lst)))
	{
		free(l);
		return (NULL);
	}
	buff = l;
	while (lst->next)
	{
		lst = lst->next;
		if (!(buff->next = f(lst)))
		{
			ft_delete(&l);
			return (NULL);
		}
		buff = buff->next;
	}
	return (l);
}
