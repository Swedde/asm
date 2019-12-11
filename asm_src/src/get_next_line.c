/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 01:43:43 by swedde            #+#    #+#             */
/*   Updated: 2019/09/24 15:11:49 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

t_g_list	*ft_lst(int fd, t_g_list **sw)
{
	t_g_list	*l;
	t_g_list	*buff;

	l = *sw;
	if (l && l->sfd == fd)
		return (l);
	while (l)
	{
		if (l->next && l->next->sfd == fd)
			return (l->next);
		if (l->next)
			l = l->next;
		else
			break ;
	}
	if (!(buff = (t_g_list *)malloc(sizeof(t_g_list))))
		return (NULL);
	buff->content = NULL;
	buff->sfd = fd;
	buff->next = NULL;
	if (l)
		l->next = buff;
	else
		*sw = buff;
	return (buff);
}

char		*ft_realloc(char **arr, char *buf, int size, int ret)
{
	char	*arr_new;
	int		i;

	if (!(arr_new = (char*)malloc(sizeof(char) * (size + ret + 1))))
		return (NULL);
	ft_noarstrcpy(arr_new, *arr);
	i = 0;
	while (buf[i])
	{
		arr_new[size + i] = buf[i];
		i++;
	}
	arr_new[size + i] = '\0';
	ft_strdel(arr);
	return (arr_new);
}

int			ft_reading(int fd, char **s, char **buff)
{
	int		res;
	int		size;

	size = (int)ft_strlen(*s);
	while (ft_strchr((const char *)*s, (int)'\n') == NULL)
	{
		res = read(fd, *buff, BUFF_SIZE);
		if (res > 0)
		{
			(*buff)[res] = '\0';
			*s = ft_realloc(s, *buff, size, res);
			size += res;
		}
		if (res == 0 && size == 0)
			return (0);
		if (res < 0)
			return (-1);
		if (res == 0 && size != 0)
			return (1);
	}
	return (1);
}

char		*ft_record(char **s)
{
	size_t		i;
	char		*line;
	char		*content;

	i = 0;
	while ((*s)[i] && (*s)[i] != '\n')
		i++;
	if ((*s)[i])
	{
		if (!(line = ft_strsub((char const *)*s, 0, i)))
			return (NULL);
		if (!(content = ft_strsub((char const *)*s, i + 1,
		ft_strlen(*s) - i - 1)))
			return (NULL);
		ft_strdel(s);
		*s = content;
		content = NULL;
	}
	else
	{
		if (!(line = ft_strsub((char const *)*s, 0, i)))
			return (NULL);
		ft_strdel(s);
	}
	return (line);
}

int			get_next_line(const int fd, char **line)
{
	static t_g_list		*sw;
	int					f;
	t_g_list			*l;
	char				*buff;

	if (fd < 0 || !line)
		return (-1);
	if (!(buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	l = ft_lst(fd, &sw);
	if (l == NULL)
	{
		ft_strdel(&buff);
		return (-1);
	}
	f = 1;
	if (ft_strchr((const char *)l->content, (int)'\n') == NULL)
		f = ft_reading(fd, &(l->content), &buff);
	if (f == 1 && l->content)
		*line = ft_record(&(l->content));
	ft_strdel(&buff);
	if (*line == NULL)
		return (-1);
	return (f);
}
