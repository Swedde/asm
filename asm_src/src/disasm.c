/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 16:23:30 by nsheev            #+#    #+#             */
/*   Updated: 2020/01/22 18:06:06 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <asm.h>

char	*get_file_string(int fd)
{
    char    *file;
	char	*line;
	char	*buf;

	file = ft_strnew(0);
	buf = ft_strnew(1);
	while (read(fd, buf, 1) == 1)
	{
		line = file;
		file = ft_strjoin(line, buf);
		ft_strdel(&line);
	}
	ft_strdel(&buf);
	return (file);
}

int		main(int ac, char **av)
{
    int		fd_s;
	int		fd_cor;
    char	*file;
    char	c;
	int		i;

	file = get_file_string(fd_cor = open(av[1], O_RDWR));
	fd_s = open("out.s", O_RDWR | O_CREAT | O_TRUNC, 0777);
	write(fd_s, ".name \"", 7);
	i = 0;
	while (i < 4)
	{
		read(fd_cor, &c, 1);
		i++;
	}
	i = 0;
	while (i < PROG_NAME_LENGTH)
	{
		read(fd_cor, &c, 1);
		write(fd_s, &c, 1);
		i++;
	}
	return (0);
}