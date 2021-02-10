/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: out-nasybullin-mr <out-nasybullin-mr@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:07:35 by sdiego            #+#    #+#             */
/*   Updated: 2021/02/02 22:01:57 by out-nasybul      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	check_camera_from(t_sdl *sdl, t_world *c)
{
	if (KEY == SDLK_q)
		c->from_x += 0.5;
	else if (KEY == SDLK_w)
		c->from_x -= 0.5;
	else if (KEY == SDLK_e)
		c->from_y += 0.5;
	else if (KEY == SDLK_r)
		c->from_y -= 0.5;
	else if (KEY == SDLK_t)
		c->from_z += 0.5;
	else if (KEY == SDLK_y)
		c->from_z -= 0.5;
	sdl->progress = 0;
}

void	check_camera_to(t_sdl *sdl, t_world *c)
{
	if (KEY == SDLK_a)
		c->to_x += 0.5;
	else if (KEY == SDLK_s)
		c->to_x -= 0.5;
	else if (KEY == SDLK_d)
		c->to_y += 0.5;
	else if (KEY == SDLK_f)
		c->to_y -= 0.5;
	else if (KEY == SDLK_g)
		c->to_z += 0.5;
	else if (KEY == SDLK_h)
		c->to_z -= 0.5;
	sdl->progress = 0;
}

void	check_camera_up(t_sdl *sdl, t_world *c)
{
	if (KEY == SDLK_z)
		c->up_x += 0.5;
	else if (KEY == SDLK_x)
		c->up_x -= 0.5;
	else if (KEY == SDLK_c)
		c->up_y += 0.5;
	else if (KEY == SDLK_v)
		c->up_y -= 0.5;
	else if (KEY == SDLK_b)
		c->up_z += 0.5;
	else if (KEY == SDLK_n)
		c->up_z -= 0.5;
	sdl->progress = 0;
}

void	check_camera_position(t_sdl *sdl, t_world *w)
{
	if (KEY == SDLK_q || KEY == SDLK_w || KEY == SDLK_e || KEY == SDLK_r ||
	KEY == SDLK_t || KEY == SDLK_y)
		check_camera_from(sdl, w);
	if (KEY == SDLK_a || KEY == SDLK_s || KEY == SDLK_d || KEY == SDLK_f ||
	KEY == SDLK_g || KEY == SDLK_h)
		check_camera_to(sdl, w);
	if (KEY == SDLK_z || KEY == SDLK_x || KEY == SDLK_c || KEY == SDLK_v ||
	KEY == SDLK_b || KEY == SDLK_n)
		check_camera_up(sdl, w);
	if (sdl->progress == 0)
		w->c.transform = view_transform(
		set_v_p(w->from_x, w->from_y, w->from_z, 1),
		set_v_p(w->to_x, w->to_y, w->to_z, 1),
		set_v_p(w->up_x, w->up_y, w->up_z, 0));
}
