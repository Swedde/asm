/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_nam_com_to_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swedde <swedde@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 17:22:43 by swedde            #+#    #+#             */
/*   Updated: 2019/12/25 17:23:26 by swedde           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	write_string_to_file(int fd, char *s, int len)
{
	int				i;
	unsigned char	c;

	i = 0;
	while (s[i])
	{
		c = s[i];
		write(fd, &c, 1);
		i++;
	}
	c = 0;
	while (i < len)
	{
		write(fd, &c, 1);
		i++;
	}
	return (0);
}

int			write_nam_com_to_file(t_all *gen, int len, int type)
{
	t_token*	token;

	token = gen->token;
	while (token->type != type)
		token = token->next;
	if (ft_strlen(token->content) > len)
	{
		print_point(token->point);
		ft_putstr(": Constant error:\n\t");
		print_token(token);
		ft_putendl(" size exceeded");
		do_exit(NULL, gen);
	}
	write_string_to_file(gen->fd, token->content, len);
	write_int_to_file(gen, 0);
	return (1);
}
