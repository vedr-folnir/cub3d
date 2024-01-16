/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:37:40 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/16 16:39:46 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./cub3D.h"

void	collision(int keycode, t_player *p, t_map *m, int xo)
{
	int	yo;

	if (p->dy < 0)
		yo = -25;
	else
		yo = 25;
	if (keycode == 's')
	{
		if (m->map[(int)(p->y / 64) * m->width
			+ (int)((p->x - xo) / 64)] != '1')
			p->x -= p->dx * 1.3;
		if (m->map[(int)((p->y - yo) / 64) *m->width
			+ (int)(p->x / 64)] != '1')
			p->y -= p->dy * 1.3;
	}
	if (keycode == 'w')
	{
		if (m->map[(int)(p->y / 64) * m->width
			+ (int)((p->x + xo) / 64)] != '1')
			p->x += p->dx * 1.3;
		if (m->map[(int)((p->y + yo) / 64) *m->width
			+ (int)(p->x / 64)] != '1')
			p->y += p->dy * 1.3;
	}
}

void	left_side(t_player *p, t_map *m, int yo, int xo)
{
	if (fmod(p->a, (2 * M_PI)) > 3 * M_PI / 2 || (fmod(p->a, (2 * M_PI))
			> M_PI / 2 && fmod(p->a, (2 * M_PI)) < M_PI))
	{
		if (m->map[(int)(p->y / 64) * m->width + (int)((p->x - xo) / 64)]
			!= '1')
			p->x += 5 * cos(-M_PI / 2 + p->a);
		if (m->map[(int)((p->y + yo) / 64) *m->width + (int)(p->x / 64)]
			!= '1')
			p->y += 5 * sin(-M_PI / 2 + p->a);
	}
	else
	{
		if (m->map[(int)(p->y / 64) * m->width + (int)((p->x + xo) / 64)]
			!= '1')
			p->x += 5 * cos(-M_PI / 2 + p->a);
		if (m->map[(int)((p->y - yo) / 64) *m->width + (int)(p->x / 64)]
			!= '1')
			p->y += 5 * sin(-M_PI / 2 + p->a);
	}
}

void	right_side(t_player *p, t_map *m, int yo, int xo)
{
	if (fmod(p->a, (2 * M_PI)) < M_PI / 2 || (fmod(p->a, (2 * M_PI))
			> M_PI && fmod(p->a, (2 * M_PI)) < 3 * M_PI / 2))
	{
		if (m->map[(int)(p->y / 64) * m->width
			+ (int)((p->x - xo) / 64)] != '1')
			p->x += 5 * cos(M_PI / 2 + p->a);
		if (m->map[(int)((p->y + yo) / 64) *m->width
			+ (int)(p->x / 64)] != '1')
			p->y += 5 * sin(M_PI / 2 + p->a);
	}
	else
	{
		if (m->map[(int)(p->y / 64) * m->width
			+ (int)((p->x + xo) / 64)] != '1')
			p->x += 5 * cos(M_PI / 2 + p->a);
		if (m->map[(int)((p->y - yo) / 64) *m->width
			+ (int)(p->x / 64)] != '1')
			p->y += 5 * sin(M_PI / 2 + p->a);
	}
}

void	collision_side(int keycode, t_player *p, t_map *m)
{
	int	xo;
	int	yo;

	if (p->dx < 0)
		xo = -25;
	else
		xo = 25;
	if (p->dy < 0)
		yo = -25;
	else
		yo = 25;
	if (keycode == 'a')
	{
		left_side(p, m, yo, xo);
	}
	if (keycode == 'd')
		right_side(p, m, yo, xo);
}
