/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 19:38:02 by nsheev            #+#    #+#             */
/*   Updated: 2019/09/14 19:38:34 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char	*s;
	size_t			m;

	s = (unsigned char*)destination;
	m = 0;
	while (m < n)
	{
		*(s++) = (unsigned char)c;
		m++;
	}
	return (destination);
}
