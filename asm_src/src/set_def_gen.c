/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_def_gen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:29:01 by nsheev            #+#    #+#             */
/*   Updated: 2019/12/12 15:34:03 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		get_file_name(t_all* gen, char *s)
{
	char	*tmp;
	int i;

	tmp = NULL;
	i = ft_strlen(s) - 1;
	while (s[i] != '.' && i > -1)
		i--;
	if (i == -1)
		gen->file_name = ft_strjoin(s, ".cor");
	else
	{
		tmp = ft_strsub(s, 0, i);
		gen->file_name = ft_strjoin(tmp, ".cor");
		free(tmp);
	}
	return (0);
}

static t_all*	creat_t_all(void)
{
	t_all*		gen;

	gen = NULL;
	gen = (t_all*)malloc(sizeof(t_all));
	if (!gen)
	{
		ft_putendl("Error: didn't allocated memory");
		exit(-1);
	}
	gen->fd				= 0;
	gen->fd_s			= 0;
	gen->file_name		= NULL;
	gen->comment		= NULL;
	gen->name			= NULL;
	gen->token			= NULL;
	gen->file			= NULL;
	gen->error			= NULL;
	return (gen);
}

int				get_file(t_all* gen)
{
	char*	line;
	char*	buf;

	gen->file = ft_strnew(0);
	buf = ft_strnew(1);
	while (read(gen->fd_s, buf, 1) == 1)
	{
		line = gen->file;
		gen->file = ft_strjoin(line, buf);
		ft_strdel(&line);
	}
	ft_strdel(&buf);
	return (0);
}

t_all*			set_def_gen(char *s)
{
	t_all*	gen;
	char*	tmp;

	gen = creat_t_all();
	get_file_name(gen, s);
	if (((gen->fd_s = open(s, O_RDONLY)) == -1) || (read(gen->fd_s, tmp, 0) < 0))
	{
		tmp = ft_strjoin("Can't read source file ", s);
		do_exit(&tmp, gen);
	}
	get_file(gen);
	close(gen->fd_s);
	return (gen);
}
