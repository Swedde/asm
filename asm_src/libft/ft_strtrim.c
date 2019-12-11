/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:58:47 by nsheev            #+#    #+#             */
/*   Updated: 2019/09/16 21:28:00 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int start;
	int end;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		start++;
	end = ft_strlen(s) - 1;
	while (end && (s[end] == ' ' || s[end] == '\n' || s[end] == '\t'))
		end--;
	return (end - start + 1 < 0 ? ft_strsub(s, start, 0) :
	ft_strsub(s, start, end - start + 1));
}
