/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 14:21:10 by mgalt             #+#    #+#             */
/*   Updated: 2021/02/14 17:04:16 by mgalt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	read_config(t_sdl *sdl, t_world *w, t_data *p, char *path)
{
	SDL_RenderClear(sdl->ren);
	SDL_RenderPresent(sdl->ren);
	bzero(sdl->img, WIN_H * WIN_W * sizeof(int));
	sdl->run = 0;
	p->obj_n = 0;
	p->fd = 0;
	w->light_obj = 0;
	if (check_format(path) != 1)
	{
		ft_putendl("\nWrong Format or invalid file\n");
		exit(1);
	}
	p->file = ft_strdup(path);
	read_file(path, p, w);
	sdl->progress = 0;
	w->s_obj = p->sp_num;
	w->pl_obj = p->pl_num;
	w->cone_obj = p->cone_num;
	w->cyl_obj = p->cyl_num;
	w->cub_obj = p->cube_num;
	w->trian_obj = p->tri_num;
	w->max_obj = p->obj_n;
	w->ar_count = 0;
	pushing_objects(p, w);
}
