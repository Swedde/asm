/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:48:57 by swedde            #+#    #+#             */
/*   Updated: 2019/12/12 18:16:58 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
/*
int		write_string_to_file(int fd, char*	s,	int len)
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

int		write_name_and_comment_to_file(t_all* gen)
{
	get_name_and_comment(gen);
	if (ft_strlen(gen->name) > PROG_NAME_LENGTH)
		gen->fatal = 1;
	if (ft_strlen(gen->comment) > COMMENT_LENGTH)
		gen->fatal = 1;
	if (gen->fatal)
	{
		ft_putendl("Something goes wrong...");
		exit(-1);
	}
	write_string_to_file(gen->fd, gen->name, PROG_NAME_LENGTH);
	write_int_to_file(gen, 0);
	write_int_to_file(gen, CHAMP_MAX_SIZE);
	write_string_to_file(gen->fd, gen->comment, COMMENT_LENGTH);
	write_int_to_file(gen, 0);
	return (0);
}
*/

int     main(int ac, char **av)
{
	t_all*		gen;

	gen = set_def_gen(av[ac-1]);
	reading(gen);
	ft_putendl(gen->name);
	ft_putendl(gen->comment);
	if ((gen->fd = open(gen->file_name, O_RDWR|O_CREAT|O_TRUNC, 0777)) == -1)
	{
		write(1, "errorInOpenFd\n", 12);
		exit(-1);
	}
	/*
	write_int_to_file(gen, COREWAR_EXEC_MAGIC);
	write_name_and_comment_to_file(gen);
    close(gen->fd);
	close(gen->fd_s);*/
	do_exit(NULL, gen);
    return (0);
}
