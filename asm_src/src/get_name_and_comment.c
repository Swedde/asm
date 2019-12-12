/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_and_comment.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 00:56:53 by swedde            #+#    #+#             */
/*   Updated: 2019/12/12 13:51:35 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_name_and_comment(t_all* gen)
{
	char*	gnl; //res of gnl
	int		i;
	char*	tmp;//to search second "
	char*	buf;

	gnl = NULL;
	//иду по строке, пока не найду символ
	while (!gen->comment || !gen->name)
	{
		ft_strdel(&gnl);
		if (get_next_line(gen->fd_s, &gnl) < 1)
		{
			break;
		}
		i = 0;
		while ((gnl[i] == ' ' || gnl[i] == '\t') && gnl[i] != '\0')
			i++;
		if (gnl[i] == '\0' || gnl[i] == COMMENT_CHAR)
			continue;
		//проверяю команду имени
		if (gnl && !ft_strcmp(&gnl[i], ft_strstr(&gnl[i], NAME_CMD_STRING)))
		{
			//если имя уже есть выход
			if (gen->name)
			{
				ft_putendl("secondName");
				break;
			}
			i += ft_strlen(NAME_CMD_STRING) - 1;
			//ищу ковычки
			while (1)
			{
				i++;
				if (gnl[i] == '\0' || gnl[i] == COMMENT_CHAR)
				{
					ft_strdel(&gnl);
					if (get_next_line(gen->fd_s, &gnl) < 1)
					{
						ft_strdel(&gnl);
						return (-1);
					}
					i = 0;
					continue;
				}
				else if (gnl[i] == ' ' || gnl[i] == '\t')
					continue;
				else if (gnl[i] == '"')
					break;
				else
				{
					ft_strdel(&gnl);
					return (-1);
				}
			}
			//нашел первые ковычки, ищу вторые
			tmp = ft_strsub(gnl, i + 1, ft_strlen(gnl) - i);
			while (!ft_strchr(tmp, '"'))
			{
				ft_strdel(&gnl);
				if (get_next_line(gen->fd_s, &gnl) < 1)
				{
					ft_putendl("end File In Search Name");
					ft_strdel(&gnl);
					return (-1);
				}
				buf = tmp;
				tmp = ft_strjoin(tmp, gnl);
				ft_strdel(&buf);
			}
			ft_strdel(&gnl);
			//нашел вторые, проверяю отсутствие символов после ковычек
			buf = ft_strchr(tmp, '"') + 1;
			i = 0;
			while (buf[i] == ' ' || buf[i] == '\t')
				i++;
			if (buf[i] != '\0')
			{
				ft_putendl("bad Symbol In Search Name");
				ft_strdel(&tmp);
				return (-1);
			}
			i = 0;
			while (tmp[i] != '"')
				i++;
			buf = tmp;
			tmp = ft_strsub(tmp, 0, i);
			ft_strdel(&buf);
			gen->name = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		//проверяю команду comenta
		else if (gnl && !ft_strcmp(&gnl[i], ft_strstr(&gnl[i], COMMENT_CMD_STRING)))
		{
			//если comment уже есть выход
			if (gen->comment)
			{
				break;
			}
			i += ft_strlen(COMMENT_CMD_STRING) - 1;
			//ищу ковычки
			while (1)
			{
				i++;
				if (gnl[i] == '\0' || gnl[i] == COMMENT_CHAR)
				{
					ft_strdel(&gnl);
					if (get_next_line(gen->fd_s, &gnl) < 1)
					{
						ft_strdel(&gnl);
						return (-1);
					}
					i = 0;
					continue;
				}
				else if (gnl[i] == ' ' || gnl[i] == '\t')
					continue;
				else if (gnl[i] == '"')
					break;
				else
				{
					ft_strdel(&gnl);
					return (-1);
				}
			}
			//нашел первые ковычки, ищу вторые
			tmp = ft_strsub(gnl, i + 1, ft_strlen(gnl) - i);
			while (!ft_strchr(tmp, '"'))
			{
				ft_strdel(&gnl);
				if (get_next_line(gen->fd_s, &gnl) < 1)
				{
					ft_putendl("end File In Search Comment");
					ft_strdel(&gnl);
					return (-1);
				}
				buf = tmp;
				tmp = ft_strjoin(tmp, gnl);
				ft_strdel(&buf);
			}
			//нашел вторые, проверяю отсутствие символов после ковычек
			buf = ft_strchr(tmp, '"') + 1;
			i = 0;
			while (buf[i] == ' ' || buf[i] == '\t')
				i++;
			if (buf[i] != '\0')
			{
				ft_putendl("bad Symbol In Search Comment");
				ft_strdel(&tmp);
				return (-1);
			}
			i = 0;
			while (tmp[i] != '"')
				i++;
			buf = tmp;
			tmp = ft_strsub(tmp, 0, i);
			ft_strdel(&buf);
			gen->comment = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		else if (gnl)
		{
			ft_putendl(" { BAD } ");
			ft_putendl(&gnl[i]);
			break;
		}
	}
	ft_strdel(&gnl);
	return (0);
}
