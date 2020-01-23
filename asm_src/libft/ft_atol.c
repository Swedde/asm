/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:15:49 by nsheev            #+#    #+#             */
/*   Updated: 2020/01/23 03:03:32 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

long int	ft_atol(const char *str)
{
	long long int			i;
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
	if (neg == 1)
		i = i * (-1);
	return (i);
}
