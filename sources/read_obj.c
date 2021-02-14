/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 16:35:12 by mgalt             #+#    #+#             */
/*   Updated: 2021/02/14 17:08:46 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		add_vertices(t_vec *vertices, char **split, int reset)
{
	static int	i = 0;

	if (reset)
	{
		i = 0;
		return ;
	}
	vertices[i++] = set_v_p(SDL_atof(split[1]), SDL_atof(split[2]), SDL_atof(split[3]), 1);
}

static void		get_indexes(char **split, int *indexes, int max_index)
{
	int			i;
	int			number;

	i = -1;
	while (++i < 3)
	{
		number = SDL_atoi(split[i + 1]);
		if (number <= 0 || number > max_index)
			ft_crash("Vertex index error");
		indexes[i] = number - 1;
	}
}

static void		add_triangles(char ***pointer, t_vec *vertices, t_data *p, t_world *w)
{
	t_forcam	forcam;
	int			indexes[3];

	get_indexes(pointer[0], indexes, p->vertex_count);
	forcam.from = vertices[indexes[0]];
	forcam.to = vertices[indexes[1]];
	forcam.up = vertices[indexes[2]];
	p->is_obj_file = 1;
	p->tr_vec = forcam;
	set_trian(p->tr_vec.from, p->tr_vec.to, p->tr_vec.up, &w->trian[p->tri_i]);
	w->trian[p->tri_i].m = default_material();
	++p->tri_i;
}

void			read_obj(const char *path, t_data *p, t_world *w, char **tab)
{
	const int	fd = ft_open_file(path);
	char		*line;
	char		**split;
	t_vec		*vertices;

	int lin = 1;
	if (!(vertices = malloc(sizeof(t_vec) * p->vertex_count)))
		ft_crash("Vertices malloc error");
	printf("%d, %d", p->vertex_count, p->tri_num);
	add_vertices(NULL, NULL, 1);
	int ret;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		split = ft_strsplit(line, ' ');
		if (tab_length(split) != 4)
			ft_crash("obj file error");
		if (!SDL_strcmp(split[0], "v"))
			add_vertices(vertices, split, 0);
		else if (!SDL_strcmp(split[0], "f"))
			add_triangles((char**[2]){split, tab}, vertices, p, w);
		else if (split[0][0] != '#')
			ft_crash("simple obj reader supports only f, v, and comments");
		free_tab(split);
		free(line);
	}
	close(fd);
	free(vertices);
}
