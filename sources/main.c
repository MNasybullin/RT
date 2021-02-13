/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:12:33 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/13 20:09:27 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	quit(t_sdl *sdl, int error)
{
	if (sdl->text != NULL)
		SDL_DestroyTexture(sdl->text);
	sdl->text = NULL;
	if (sdl->img != NULL)
		free(sdl->img);
	SDL_FreeSurface(sdl->icon);
	SDL_DestroyRenderer(sdl->ren);
	SDL_DestroyWindow(sdl->win);
	SDL_Quit();
	exit(error);
}

void	key_press(t_sdl *sdl, t_world *w, t_data *p, char *path)
{
	if (KEY == SDLK_ESCAPE)
		sdl->run = 1;
	else if (KEY == SDLK_F12)
		save_texture(sdl->ren, sdl->text);
	else if (KEY == SDLK_1 || KEY == SDLK_2 || KEY == SDLK_3 || KEY == SDLK_o)
	{
		if (KEY == SDLK_1)
			w->c.aliasing = w->c.aliasing == 0 ? 1 : 0;
		else if (KEY == SDLK_2)
			w->c.sepia = w->c.sepia == 0 ? 1 : 0;
		else if (KEY == SDLK_3)
			w->effective_render = w->effective_render == 0 ? 1 : 0;
		else if (KEY == SDLK_o)
		{
			w->obj_ar[0].m->color.r += 0.2;
			w->obj_ar[0].m->color.g += 0.3;
			w->obj_ar[0].m->color.b += 0.5;
		}
		sdl->progress = 0;
	}
	else if (KEY == SDLK_n && !(sdl->progress = 0))
		read_config(sdl, w, p, path);
	if (w->effective_render == 1)
		check_camera_position(sdl, w);
	if (sdl->progress == 0)
		SDL_SetWindowTitle(sdl->win, "RT - Rendering in progress ...");
}

void	init_sdl_error(void)
{
	write(2, "SDL Init Error\n", 15);
	exit(EXIT_FAILURE);
}

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

void			add_vertices(t_vec *vertices, char **split, int reset)
{
	static int	i = 0;

	if (reset)
	{
		i = 0;
		return ;
	}
	vertices[i] = set_v_p(SDL_atof(split[1]), SDL_atof(split[2]), SDL_atof(split[3]), 1);
}

void			get_indexes(char **split, int *indexes, int max_index)
{
	int			i;
	int			number;

	i = -1;
	while (++i < 3)
	{
		number = SDL_atoi(split[i + 1]);
		if (number <= 0 || number > max_index)
			ft_crash("Vertex index error");
		indexes[i] = number;
	}
}

void			add_triangles(char ***pointer, t_vec *vertices, t_data *p, t_world *w)
{
	t_forcam	forcam;
	int			indexes[3];
	
	get_indexes(pointer[0], indexes, p->vertex_count);
	forcam.from = vertices[indexes[0]];
	forcam.to = vertices[indexes[1]];
	forcam.up = vertices[indexes[2]];
	p->is_obj_file = 1;
	p->tr_vec = forcam;
	make_tri(p, w, pointer[1]);
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
	add_vertices(NULL, NULL, 1);
	int ret;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		printf("line is %d\n", lin++);
		split = ft_strsplit(line, ' ');
		if (tab_length(split) != 4)
			ft_crash("obj file error");
		if (!SDL_strcmp(split[0], "v"))
		{
			printf("adding verticle\n");
			add_vertices(vertices, split, 0);
		}
		else if (!SDL_strcmp(split[0], "f"))
		{
			printf("adding triange\n");
			add_triangles((char**[2]){split, tab}, vertices, p, w);
		}
		else if (split[0][0] != '#')
			ft_crash("simple obj reader supports only f, v, and comments");
		free_tab(split);
		free(line);
	}
	printf("%d\n", ret);
}

void	init(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		init_sdl_error();
	if ((sdl->win = SDL_CreateWindow("RT", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_SHOWN)) == NULL)
		init_sdl_error();
	if ((sdl->icon = SDL_LoadBMP("icon.bmp")) == NULL)
		init_sdl_error();
	SDL_SetWindowIcon(sdl->win, sdl->icon);
	if ((sdl->ren = SDL_CreateRenderer(sdl->win, -1, 0)) == NULL)
		init_sdl_error();
	if ((sdl->text = SDL_CreateTexture(sdl->ren, SDL_PIXELFORMAT_ARGB8888,
	SDL_TEXTUREACCESS_STREAMING, WIN_W, WIN_H)) == NULL)
		init_sdl_error();
	if ((sdl->img = malloc(WIN_W * WIN_H * sizeof(int))) == NULL)
		init_sdl_error();
}

int		main(int ac, char **av)
{
	t_sdl		sdl;
	t_world		w;
	t_data		p;

	if (ac == 2)
	{
		init(&sdl);
		read_config(&sdl, &w, &p, av[1]);
	}
	else
	{
		ft_putendl("\nUsage: ./RT <file.yml>\n");
		return (1);
	}
	w.effective_render = 0;
	SDL_SetWindowTitle(sdl.win, "RT - Rendering in progress ...");
	while (sdl.run == 0)
	{
		while (SDL_PollEvent(&sdl.e) != 0)
		{
			if (sdl.e.type == SDL_QUIT)
				sdl.run = 1;
			if (sdl.e.type == SDL_KEYDOWN)
				key_press(&sdl, &w, &p, av[1]);
		}
		if (sdl.progress == 0)
		{
			render(&sdl, w.c, w);
			SDL_SetWindowTitle(sdl.win, "RT");
			sdl.progress++;
		}
	}
	quit(&sdl, EXIT_SUCCESS);
	return (0);
}
