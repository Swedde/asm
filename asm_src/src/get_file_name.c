/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 22:08:30 by swedde            #+#    #+#             */
/*   Updated: 2019/12/11 22:08:54 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char*	get_file_name(char *s)
{
	char	*name;
	char	*tmp;
	int i;

	name = NULL;
	tmp = NULL;
	i = ft_strlen(s) - 1;
	while (s[i] != '.' && i > -1)
		i--;
	if (i > 0)
	{
		tmp = ft_strsub(s, 0, i);
		name = ft_strjoin(tmp, ".cor");
		free(tmp);
	}
	return (name);
}
