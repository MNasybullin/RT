/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalt <mgalt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:12:33 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/14 13:49:33 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		sdl_events(t_sdl *sdl, t_world *w, t_data *p, char *av)
{
	char	*line;

	if (sdl->e.type == SDL_QUIT)
		sdl->run = 1;
	if (sdl->e.type == SDL_KEYDOWN)
		key_press(sdl, w, p, av);
	if (sdl->e.type == SDL_DROPFILE)
	{
		line = sdl->e.drop.file;
		read_config(sdl, w, p, line);
		free(line);
	}
}
