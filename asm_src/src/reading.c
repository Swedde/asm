/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:32:55 by nsheev            #+#    #+#             */
/*   Updated: 2019/12/12 18:40:20 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	increment_point(t_point *point, int* i,  char c)
{
	if (c == '\n')
	{
		(*point).x++;
		(*point).y = -1;
	}
	(*point).y++;
	(*i)++;
	return (0);
}

int			reading(t_all*	gen)
{
	t_point		point;
	int			i;
	int			j;
	int			j1;
	char*		error;
	char*		tmp;
	char*		buf;

	point.x = 1;
	point.y = 0;
	i = 0;
	while (gen->file[i])
	{
		while ((gen->file[i] == ' ' || gen->file[i] == '\t' || gen->file[i] == '\n') && gen->file[i])
			increment_point(&point, &i, gen->file[i]);
		if (gen->file[i] == COMMENT_CHAR || gen->file[i] == ';')
			while (gen->file[i] != '\n' && gen->file[i])
				i++;
		else if (!ft_strcmp(&gen->file[i], ft_strstr(&gen->file[i], NAME_CMD_STRING)))
		{
			j = i + ft_strlen(NAME_CMD_STRING);
			//ищу ковычки
			while (gen->file[j] != '"')
			{
				while ((gen->file[j] == ' ' || gen->file[j] == '\t') && gen->file[j])
					increment_point(&point, &j, gen->file[j]);
				if (gen->file[j] == '\0')
				{
					error = ft_strdup("Syntax error at token [TOKEN][???:???] END \"(null)\"");
					do_exit(&error, gen);
				}
				else if (gen->file[j] == '\n')
				{
					error = ft_strdup("Syntax error at token [TOKEN][???:???] ENDLINE");
					do_exit(&error, gen);
				}
				else if (gen->file[j] != '"')
				{
					error = ft_strdup("Lexical error at [???:???]");
					do_exit(&error, gen);
				}
			}
			//нашел первые ковычки, ищу вторые
			tmp = ft_strsub(gen->file, j + 1, ft_strlen(gen->file) - j);
			buf = tmp;
			j1 = 0;
			while (buf[j1] != '"' && buf[j1])
				j1++;
			if (!buf[j1])
			{
				error = ft_strdup("End file in searching second \"");
				do_exit(&error, gen);
			}
			tmp = ft_strsub(tmp, 0, j1);
			ft_strdel(&buf);
			gen->name = ft_strdup(tmp);
			ft_strdel(&tmp);
			i = i + j + j1 + 2;
			ft_putendl(gen->name);
		}
		else if (!ft_strcmp(&gen->file[i], ft_strstr(&gen->file[i], COMMENT_CMD_STRING)))
		{
			ft_putendl(&gen->file[i]);
			j = i + ft_strlen(COMMENT_CMD_STRING);
			//ищу ковычки
			while (gen->file[j] != '"')
			{
				while ((gen->file[j] == ' ' || gen->file[j] == '\t') && gen->file[j])
					increment_point(&point, &j, gen->file[j]);
				if (gen->file[j] == '\0')
				{
					error = ft_strdup("Syntax error at token [TOKEN][???:???] END \"(null)\"");
					do_exit(&error, gen);
				}
				else if (gen->file[j] == '\n')
				{
					error = ft_strdup("Syntax error at token [TOKEN][???:???] ENDLINE");
					do_exit(&error, gen);
				}
				else if (gen->file[j] != '"')
				{
					error = ft_strdup("Lexical error at [???:???]");
					do_exit(&error, gen);
				}
			}
			//нашел первые ковычки, ищу вторые
			tmp = ft_strsub(gen->file, j + 1, ft_strlen(gen->file) - j);
			buf = tmp;
			j1 = 0;
			while (buf[j1] != '"' && buf[j1])
				j1++;
			if (!buf[j1])
			{
				error = ft_strdup("End file in searching second \"");
				do_exit(&error, gen);
			}
			tmp = ft_strsub(tmp, 0, j1);
			ft_strdel(&buf);
			gen->comment = ft_strdup(tmp);
			ft_strdel(&tmp);
			i = i + j + j1 + 2;
			ft_putendl(gen->name);
		}
		else
			i++;
	}
	return (0);
}