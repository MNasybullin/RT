/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 11:31:37 by mgalt             #+#    #+#             */
/*   Updated: 2021/02/14 12:50:59 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			get_obj_triangle_count(const char *path, t_data *p)
{
	const int	fd = ft_open_file(path);
	char		*line;

	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == 'v')
			++p->vertex_count;
		if (line[0] == 'f')
			++p->tri_num;
		free(line);
	}
	close(fd);
}

void	make_obj_from_file(t_data *p, t_world *w, char **tab)
{
    char	*path;

	path = NULL;
    init_tri(p, w);
	while ((get_next_line(p->fd, &p->line)))
	{
		p->tab = ft_strsplit(p->line, ' ');
		if (len_tab(p->tab) == 0)
			exit(err_wrong_format());
		if ((check_make_obj(p->tab)))
		{
			if (len_tab(p->tab) == 2 && !(ft_strcmp(p->tab[0], "path:")))
			{
				path = ft_strdup(remove_quotes(p->tab[1]));
				read_obj(path, p, w, tab);
				free(path);
			}
		}
		else
			break ;
	}
	p->is_obj_file = 0;
	p->tri_i++;
}
