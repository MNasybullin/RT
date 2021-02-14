/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 14:55:38 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/14 16:21:25 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			my_read(const int fd, char **content)
{
	int		read_result;
	char	*tmp;
	char	buf[BUFF_SIZE + 1];

	while ((read_result = read(fd, buf, BUFF_SIZE)))
	{
		buf[read_result] = '\0';
		tmp = *content;
		if (!(*content = ft_strjoin(*content, buf)))
			return (-1);
		free(tmp);
		if (ft_strchr(buf, ENDL))
			break ;
	}
	return (read_result);
}

int			get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	size_t			read_result;
	static t_list	*hist;
	t_list			*live;
	char			*tmp;

	if (fd < 0 || !line || (read(fd, buf, 0)) < 0 ||
		(!(live = get_live(fd, &hist))))
		return (-1);
	tmp = live->content;
	read_result = my_read(fd, &tmp);
	live->content = tmp;
	if (!read_result && !*tmp)
		return (0);
	read_result = line_copy(line, live->content, ENDL);
	tmp = live->content;
	if (tmp[read_result] != '\0')
	{
		live->content = ft_strdup(&((live->content)[read_result + 1]));
		free(tmp);
	}
	else
		tmp[0] = '\0';
	return (1);
}

void		check_tab_len(char **tab)
{
	if (len_tab(tab) != 2)
	{
		free_tab(tab);
		exit(-1);
	}
}

int			tab_length(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		;
	return (i);
}

int			ft_strequ(char const *s1, char const *s2)
{
	char	*new1;
	char	*new2;

	if (s1 && s2)
	{
		new1 = (char *)s1;
		new2 = (char *)s2;
		if (ft_strcmp(new1, new2) == 0)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}
