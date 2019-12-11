/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 19:39:28 by nsheev            #+#    #+#             */
/*   Updated: 2019/09/14 19:40:02 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*s1;
	int		l;

	if (!dest && !src)
		return (NULL);
	if (src < dest)
	{
		l = (int)n - 1;
		s = (char *)dest;
		s1 = (char *)src;
		while (l >= 0)
		{
			s[l] = s1[l];
			l--;
		}
		return (dest);
	}
	else
		return (ft_memcpy(dest, src, n));
}
