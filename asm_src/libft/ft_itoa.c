/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:58:47 by nsheev            #+#    #+#             */
/*   Updated: 2019/09/14 19:34:17 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	l;

	if (n <= 0)
	{
		l = 1;
		n = -n;
	}
	else
		l = 0;
	while (n)
	{
		l = l + 1;
		n = n / 10;
	}
	return (l);
}

static int	ft_neg(char *s, int n)
{
	if (n >= 0)
		return (n);
	*s = '-';
	if (n == -2147483648)
	{
		s[1] = '2';
		n = 147483648;
	}
	else
		n = -n;
	return (n);
}

char		*ft_itoa(int n)
{
	char	*s;
	int		l;
	int		i;

	l = ft_len(n);
	if (!(s = (char *)malloc(sizeof(char) * (l + 1))))
		return (NULL);
	n = ft_neg(s, n);
	i = l - 1;
	if (!n)
		s[0] = '0';
	while (n)
	{
		s[i--] = n % 10 + '0';
		n = n / 10;
	}
	s[l] = '\0';
	return (s);
}
