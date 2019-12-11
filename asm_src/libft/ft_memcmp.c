/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 19:40:32 by nsheev            #+#    #+#             */
/*   Updated: 2019/09/14 19:41:22 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *l1;
	unsigned char *l2;

	l1 = (unsigned char *)s1;
	l2 = (unsigned char *)s2;
	while (n-- > 0)
	{
		if (*l1 != *l2)
			return (*l1 - *l2);
		l1++;
		l2++;
	}
	return (0);
}
