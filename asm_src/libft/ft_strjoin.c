/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:58:47 by nsheev            #+#    #+#             */
/*   Updated: 2019/09/16 20:50:23 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*s;
	int		j;

	if (s1 && s2)
	{
		i = ft_strlen(s1) + ft_strlen(s2);
		if (!(s = (char *)malloc((sizeof(char) * (i + 1)))))
			return (NULL);
		i = 0;
		j = 0;
		while (s1[i])
		{
			s[i] = s1[i];
			i++;
		}
		while (s2[j])
		{
			s[i + j] = s2[j];
			j++;
		}
		s[i + j] = '\0';
		return (s);
	}
	return (NULL);
}
