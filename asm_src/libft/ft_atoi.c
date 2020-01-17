/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:15:49 by nsheev            #+#    #+#             */
/*   Updated: 2020/01/17 19:26:16 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

unsigned long int	ft_atoi(const char *str)
{
	unsigned long long int	i;
	int						neg;

	neg = 0;
	i = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' ||
	*str == '\r' || *str == '\v' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		i = i * 10 + *str - 48;
		str++;
	}
	if (i > 4294967295)
		return (4294967295);
	if (i > 4294967295 && neg)
		return (0);
	if (neg == 1)
		i = i * (-1);
	return (i);
}
