/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsheev <nsheev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:32:55 by nsheev            #+#    #+#             */
/*   Updated: 2020/01/20 16:38:25 by nsheev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			is_delim(char c)
{
	if (
		c == ' ' ||
		c == '\t' ||
		c == '\n' ||
		c == SEPARATOR_CHAR ||
		c == DIRECT_CHAR ||
		c == '\0' ||
		c == LABEL_CHAR)
		return (1);
	return (0);
}

int			is_char_labl(char c, char *pattern)
{
	int i;

	i = 0;
	while (pattern[i])
	{
		if (pattern[i] == c)
			return (1);
		i++;
	}
	return (0);
}

t_point		get_point(t_all *gen)
{
	t_point	point;

	point.x = gen->point.x;
	point.y = gen->point.y;
	return (point);
}

static int	increment_point(t_all *gen)
{
	if (gen->file[gen->i] == '\n')
	{
		gen->point.x++;
		gen->point.y = 0;
	}
	gen->i++;
	gen->point.y++;
	return (0);
}

void		find_name_comment(t_all *gen, int type, char *command)
{
	int		j;
	int		j1;
	char	*tmp;
	char	*buf;

	j = gen->i + ft_strlen(command);
	while (gen->file[j] != '"' && (gen->file[j] == ' ' || gen->file[j] == '\t'))
		j++;
	if (gen->file[j] != '"' && (gen->error = ft_strdup("Name: Can't find \"")))
		do_exit(&gen->error, gen);
	tmp = ft_strsub(gen->file, j + 1, ft_strlen(gen->file) - j);
	buf = tmp;
	j1 = 0;
	while (buf[j1] != '"' && buf[j1])
		j1++;
	if (!buf[j1] && (gen->error = ft_strdup("End file in searching second \"")))
		do_exit(&gen->error, gen);
	tmp = ft_strsub(tmp, 0, j1);
	ft_strdel(&buf);
	push_tail_token(&gen->token, type, tmp, gen->point);
	ft_strdel(&tmp);
	j = j - gen->i + j1 + 2;
	while (j && (j-- || 1))
		increment_point(gen);
}

int			is_label(t_all *gen)
{
	int i;

	i = gen->i;
	if (gen->file[i] == LABEL_CHAR)
		return (0);
	while (is_char_labl(gen->file[i], LABEL_CHARS))
		i++;
	if (gen->file[i] == LABEL_CHAR)
		return (1);
	return (0);
}

int			find_label(t_all *gen)
{
	char	*tmp;
	int		j;

	j = gen->i;
	while (gen->file[j] != LABEL_CHAR)
		j++;
	tmp = ft_strsub(gen->file, gen->i, j - gen->i);
	push_tail_token(&gen->token, LABEL_TYPE, tmp, gen->point);
	ft_strdel(&tmp);
	while (j + 1 > gen->i)
		increment_point(gen);
	return (1);
}

int			is_op(t_all *gen)
{
	char	*s;

	s = &gen->file[gen->i];
	return ((!ft_strcmp(s, ft_strstr(s, "live")) && is_delim(s[4]) && s[4] !=
	LABEL_CHAR) || (!ft_strcmp(s, ft_strstr(s, "ld")) && is_delim(s[2]) && s[2]
	!= LABEL_CHAR) || (!ft_strcmp(s, ft_strstr(s, "st")) && is_delim(s[2]) &&
	s[2] != LABEL_CHAR) || (!ft_strcmp(s, ft_strstr(s, "add")) &&
	is_delim(s[3]) && s[3] != LABEL_CHAR) || (!ft_strcmp(s,
	ft_strstr(s, "sub")) && is_delim(s[3]) && s[3] != LABEL_CHAR) ||
	(!ft_strcmp(s, ft_strstr(s, "and")) && is_delim(s[3]) && s[3] !=
	LABEL_CHAR) || (!ft_strcmp(s, ft_strstr(s, "or")) && is_delim(s[2]) && s[2]
	!= LABEL_CHAR) || (!ft_strcmp(s, ft_strstr(s, "xor")) && is_delim(s[3]) &&
	s[3] != LABEL_CHAR) || (!ft_strcmp(s, ft_strstr(s, "zjmp")) &&
	is_delim(s[4]) && s[4] != LABEL_CHAR) || (!ft_strcmp(s,
	ft_strstr(s, "ldi")) && is_delim(s[3]) && s[3] != LABEL_CHAR) ||
	(!ft_strcmp(s, ft_strstr(s, "sti")) && is_delim(s[3]) && s[3] !=
	LABEL_CHAR) || (!ft_strcmp(s, ft_strstr(s, "fork")) && is_delim(s[4]) &&
	s[4] != LABEL_CHAR) || (!ft_strcmp(s, ft_strstr(s, "lld")) &&
	is_delim(s[3]) && s[3] != LABEL_CHAR) || (!ft_strcmp(s,
	ft_strstr(s, "lldi")) && is_delim(s[4]) && s[4] != LABEL_CHAR) ||
	(!ft_strcmp(s, ft_strstr(s, "lfork")) && is_delim(s[5]) && s[5] !=
	LABEL_CHAR) || (!ft_strcmp(s, ft_strstr(s, "aff")) && is_delim(s[3]) &&
	s[3] != LABEL_CHAR));
}

char		*get_op_helper(char *s)
{
	if (!ft_strcmp(s, ft_strstr(s, "or")))
		return (ft_strdup("or"));
	else if (!ft_strcmp(s, ft_strstr(s, "xor")))
		return (ft_strdup("xor"));
	else if (!ft_strcmp(s, ft_strstr(s, "zjmp")))
		return (ft_strdup("zjmp"));
	else if (!ft_strcmp(s, ft_strstr(s, "fork")))
		return (ft_strdup("fork"));
	else if (!ft_strcmp(s, ft_strstr(s, "lldi")))
		return (ft_strdup("lldi"));
	else if (!ft_strcmp(s, ft_strstr(s, "lld")))
		return (ft_strdup("lld"));
	else if (!ft_strcmp(s, ft_strstr(s, "lfork")))
		return (ft_strdup("lfork"));
	else if (!ft_strcmp(s, ft_strstr(s, "aff")))
		return (ft_strdup("aff"));
	return (NULL);
}

char		*get_op(char *s)
{
	if (!ft_strcmp(s, ft_strstr(s, "live")))
		return (ft_strdup("live"));
	else if (!ft_strcmp(s, ft_strstr(s, "ldi")))
		return (ft_strdup("ldi"));
	else if (!ft_strcmp(s, ft_strstr(s, "ld")))
		return (ft_strdup("ld"));
	else if (!ft_strcmp(s, ft_strstr(s, "sti")))
		return (ft_strdup("sti"));
	else if (!ft_strcmp(s, ft_strstr(s, "st")))
		return (ft_strdup("st"));
	else if (!ft_strcmp(s, ft_strstr(s, "add")))
		return (ft_strdup("add"));
	else if (!ft_strcmp(s, ft_strstr(s, "sub")))
		return (ft_strdup("sub"));
	else if (!ft_strcmp(s, ft_strstr(s, "and")))
		return (ft_strdup("and"));
	else
		return (get_op_helper(s));
}

void		find_op(t_all *gen)
{
	char	*tmp;
	int		j;

	tmp = get_op(&gen->file[gen->i]);
	j = ft_strlen(tmp);
	push_tail_token(&gen->token, OP_TYPE, tmp, gen->point);
	free(tmp);
	while (j)
	{
		increment_point(gen);
		j--;
	}
}

int			num_len(unsigned long num)
{
	int i;

	if (!num)
		return (1);
	i = 0;
	while (num)
	{
		i++;
		num /= 10;
	}
	return (i);
}

int			is_reg_arg(char *s)
{
	int					i;
	unsigned long int	j;
	int					a;

	if ((s[0] != 'r') || (s[1] == '+' || s[1] == '-'
		|| !(s[1] <= '9' && s[1] >= '0')))
		return (0);
	i = 1;
	if (s[i] == '0')
		i++;
	a = i;
	while (ft_isdigit(s[a]))
		a++;
	if (a > 12)
		return (0);
	if (ft_isdigit(s[i]))
	{
		j = ft_atoi(&s[i]);
		if (j > 99)
			return (0);
		i += num_len(j);
		if (is_delim(s[i]))
			return (1);
	}
	return (0);
}

void		find_reg_arg(t_all *gen)
{
	int		j;
	char	*tmp;

	j = gen->i + 1;
	while (gen->file[j] == '0')
		j++;
	j += num_len(ft_atoi(&gen->file[j]));
	tmp = ft_strsub(gen->file, gen->i + 1, j - gen->i - 1);
	push_tail_token(&gen->token, REG_ARG_TYPE, tmp, gen->point);
	ft_strdel(&tmp);
	while (j > gen->i)
		increment_point(gen);
}

int			is_dir_arg(char *s)
{
	int i;
	int a;

	if (s[0] != DIRECT_CHAR)
		return (0);
	i = 1;
	if (s[i] == '-')
		i++;
	a = 0;
	while (s[i] == '0')
		i++;
	while (ft_isdigit(s[i]))
	{
		i++;
		a++;
	}
	if (is_delim(s[i]) && ft_isdigit(s[i - 1]))
	{
		if (a > 14 || (ft_atoi(&s[1]) > 2147483647 ||
		ft_atoi(&s[1]) < -2147483648))
			return (0);
		return (1);
	}
	return (0);
}

void		find_dir_arg(t_all *gen)
{
	int		j;
	char	*tmp;

	j = gen->i + 1;
	while (gen->file[j] == ' ' || gen->file[j] == '\t')
		j++;
	if (gen->file[j] == '-')
		j++;
	while (ft_isdigit(gen->file[j]))
		j++;
	tmp = ft_strsub(gen->file, gen->i + 1, j - gen->i - 1);
	push_tail_token(&gen->token, DIR_ARG_TYPE, tmp, gen->point);
	ft_strdel(&tmp);
	while (j > gen->i)
		increment_point(gen);
}

int			is_dir_labl_arg(char *s)
{
	int i;

	if (s[0] != DIRECT_CHAR)
		return (0);
	i = 1;
	if (s[i] != LABEL_CHAR)
		return (0);
	i++;
	while (is_char_labl(s[i], LABEL_CHARS))
		i++;
	if (is_delim(s[i]) && is_char_labl(s[i - 1], LABEL_CHARS))
		return (1);
	return (0);
}

void		find_dir_labl_arg(t_all *gen)
{
	int		j;
	char	*tmp;
	int		start;

	j = gen->i + 1;
	while (gen->file[j] == ' ' || gen->file[j] == '\t')
		j++;
	start = ++j;
	while (is_char_labl(gen->file[j], LABEL_CHARS))
		j++;
	tmp = ft_strsub(gen->file, start, j - start);
	push_tail_token(&gen->token, DIR_LABL_ARG_TYPE, tmp, gen->point);
	free(tmp);
	while (j > gen->i)
		increment_point(gen);
}

int			is_ind_arg(char *s)
{
	int i;
	int a;

	if (is_delim(s[0]))
		return (0);
	i = 0;
	a = 0;
	if (s[0] == '-')
		i++;
	while (s[i] == '0')
		i++;
	while (ft_isdigit(s[i]))
	{
		i++;
		a++;
	}
	if (is_delim(s[i]) && i != 0)
	{
		if (a > 14 || (ft_atoi(s) > 2147483647 || ft_atoi(s) < -2147483648))
			return (0);
		return (1);
	}
	return (0);
}

void		find_ind_arg(t_all *gen)
{
	int		j;
	char	*tmp;
	int		start;

	j = gen->i;
	start = j;
	if (gen->file[j] == '-')
		j++;
	while (ft_isdigit(gen->file[j]))
		j++;
	tmp = ft_strsub(gen->file, start, j - start);
	push_tail_token(&gen->token, IND_ARG_TYPE, tmp, gen->point);
	free(tmp);
	while (j > gen->i)
		increment_point(gen);
}

int			is_ind_labl_arg(char *s)
{
	int i;

	if (s[0] != LABEL_CHAR)
		return (0);
	i = 1;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	while (is_char_labl(s[i], LABEL_CHARS))
		i++;
	if (is_delim(s[i]) && i > 1)
		return (1);
	return (0);
}

void		find_ind_labl_arg(t_all *gen)
{
	int		j;
	char	*tmp;
	int		start;

	j = gen->i + 1;
	while (gen->file[j] == ' ' || gen->file[j] == '\t')
		j++;
	start = j;
	while (is_char_labl(gen->file[j], LABEL_CHARS))
		j++;
	tmp = ft_strsub(gen->file, start, j - start);
	push_tail_token(&gen->token, IND_LABL_ARG_TYPE, tmp, gen->point);
	free(tmp);
	while (j > gen->i)
		increment_point(gen);
}

void		find_nl_or_separ(t_all *gen)
{
	char	*tmp;

	tmp = gen->file[gen->i] == '\n' ? char_to_string('\n') :
		char_to_string(SEPARATOR_CHAR);
	push_tail_token(&gen->token, gen->file[gen->i] == '\n' ? NL_TYPE :
		DELIM_TYPE, tmp, gen->point);
	free(tmp);
	increment_point(gen);
}

void		reading_error(t_all *gen)
{
	print_point(gen->point);
	ft_putstr(": Error: ");
	while (gen->file[gen->i] && gen->file[gen->i] != ' ' &&
		gen->file[gen->i] != '\t' && gen->file[gen->i] != '\n')
	{
		ft_putchar(gen->file[gen->i]);
		gen->i++;
	}
	write(1, "\n", 1);
	do_exit(NULL, gen);
}

void		reading_helper_2(t_all *gen)
{
	if (is_op(gen))
		find_op(gen);
	else if (is_label(gen))
		find_label(gen);
	else if (is_reg_arg(&gen->file[gen->i]))
		find_reg_arg(gen);
	else if (is_dir_arg(&gen->file[gen->i]))
		find_dir_arg(gen);
	else if (is_dir_labl_arg(&gen->file[gen->i]))
		find_dir_labl_arg(gen);
}

void		reading_helper(t_all *gen)
{
	if (gen->file[gen->i] == COMMENT_CHAR || gen->file[gen->i] == ';')
		while (gen->file[gen->i] != '\n' && gen->file[gen->i])
			increment_point(gen);
	else if (!ft_strcmp(&gen->file[gen->i], ft_strstr(&gen->file[gen->i],
	NAME_CMD_STRING)))
		find_name_comment(gen, NAME_TYPE, NAME_CMD_STRING);
	else if (!ft_strcmp(&gen->file[gen->i], ft_strstr(&gen->file[gen->i],
	COMMENT_CMD_STRING)))
		find_name_comment(gen, COMMENT_TYPE, COMMENT_CMD_STRING);
	else if (gen->file[gen->i] == '\n' || gen->file[gen->i] == SEPARATOR_CHAR)
		find_nl_or_separ(gen);
	else if (is_op(gen) || is_label(gen) || is_reg_arg(&gen->file[gen->i]) ||
	is_dir_arg(&gen->file[gen->i]) || is_dir_labl_arg(&gen->file[gen->i]))
		reading_helper_2(gen);
	else if (is_ind_arg(&gen->file[gen->i]))
		find_ind_arg(gen);
	else if (is_ind_labl_arg(&gen->file[gen->i]))
		find_ind_labl_arg(gen);
	else
		reading_error(gen);
}

int			reading(t_all *gen)
{
	while (gen->file[gen->i])
	{
		while ((gen->file[gen->i] == ' ' || gen->file[gen->i] == '\t')
		&& gen->file[gen->i])
			increment_point(gen);
		if (!gen->file[gen->i])
			break ;
		reading_helper(gen);
	}
	push_tail_token(&gen->token, END_FILE, "END FILE", gen->point);
	return (0);
}
