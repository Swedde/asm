/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 16:22:36 by nsheev            #+#    #+#             */
/*   Updated: 2019/09/16 16:35:20 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*buff;

	while (*alst != NULL)
	{
		buff = *alst;
		*alst = (*alst)->next;
		del(buff->content, buff->content_size);
		free(buff);
		buff = NULL;
	}
}
