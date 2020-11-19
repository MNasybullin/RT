/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiego <sdiego@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 19:07:35 by sdiego            #+#    #+#             */
/*   Updated: 2020/11/19 19:07:58 by sdiego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void	check_camera_from(t_sdl *sdl, t_camera *c)
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

void	check_camera_to(t_sdl *sdl, t_camera *c)
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

void	check_camera_up(t_sdl *sdl, t_camera *c)
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

void	check_camera_position(t_sdl *sdl, t_camera *c)
{
	if (KEY == SDLK_q || KEY == SDLK_w || KEY == SDLK_e || KEY == SDLK_r || KEY == SDLK_t || KEY == SDLK_y)
		check_camera_from(sdl, c);
	if (KEY == SDLK_a || KEY == SDLK_s || KEY == SDLK_d || KEY == SDLK_f || KEY == SDLK_g || KEY == SDLK_h)
		check_camera_to(sdl, c);
	if (KEY == SDLK_z || KEY == SDLK_x || KEY == SDLK_c || KEY == SDLK_v || KEY == SDLK_b || KEY == SDLK_n)
		check_camera_up(sdl, c);
	if (sdl->progress == 0)
		c->transform = view_transform(set_v_p(c->from_x, c->from_y, c->from_z, 1), set_v_p(c->to_x, c->to_y, c->to_z, 1), set_v_p(c->up_x, c->up_y, c->up_z, 0));
}
