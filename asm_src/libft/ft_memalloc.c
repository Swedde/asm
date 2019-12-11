/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:58:47 by nsheev            #+#    #+#             */
/*   Updated: 2019/09/09 14:38:13 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*s;
	size_t	i;

	if (!(s = (void *)malloc(size)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
	return (s);
}
