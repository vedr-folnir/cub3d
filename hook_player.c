/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:43:49 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/16 16:38:28 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

void	angle(int keycode, t_player *p)
{
	if (keycode == 65363)
	{
		p->a += 0.0174533 * 5;
		if (p->a > M_PI * 2)
			p->a = 0;
	}
	if (keycode == 65361)
	{
		p->a -= 0.0174533 * 5;
		if (p->a < 0)
			p->a = 2 * M_PI;
	}
	p->dx = cos(p->a) * 5;
	p->dy = sin(p->a) * 5;
}

void	finish(t_all *a)
{
	free(a->m->map_t);
	free(a->m->map);
	free(a->m->NO);
	free(a->m->SO);
	free(a->m->WE);
	free(a->m->EA);
	mlx_destroy_image(a->v->mlx, a->d->img);
	mlx_destroy_window(a->v->mlx, a->v->win);
	mlx_destroy_display(a->v->mlx);
	free(a->v->mlx);
	exit(0);
}

void	movement(int keycode, t_all *a)
{
	int	xo;

	if (a->p->dx < 0)
		xo = -25;
	else
		xo = 25;
	if (keycode == 65307)
		finish(a);
	if (keycode == 65362)
	{
		a->m->off += 5;
		if (a->m->off >= 180)
			a->m->off = 180;
	}
	if (keycode == 65364)
	{
		a->m->off -= 5;
		if (a->m->off <= -180)
			a->m->off = -180;
	}
	collision(keycode, a->p, a->m, xo);
	collision_side(keycode, a->p, a->m);
	a->m->map = door(keycode, a->p, a->m);
}
