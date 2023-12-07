/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:43:49 by hlasota           #+#    #+#             */
/*   Updated: 2023/12/04 16:56:03 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

void	angle(int keycode, t_player *p)
{
	if (keycode == 65363)
	{
		p->a += 0.1;
		if (p->a > 2 * M_PI)
			p->a = 0;
	}
	if (keycode == 65361)
	{
		p->a -= 0.1;
		if (p->a < 0)
			p->a = 2 * M_PI;
	}
	p->dx = cos(p->a) * 5;
	p->dy = sin(p->a) * 5;
}

/*void	collision(t_player *p, t_map *m)
{
	int xo;
	int yo;

	if (p->dx < 0)
		xo = -20;
	else
		xo = 20;
	if (p->dy < 0)
		yo = -20;
	else
		yo = 20;
	printf("%c\n", m->map[(int)(p->y / 64 * m->width + (p->x + xo) / 64)]);
	if (m->map[(int)(p->y / 64 * m->width + (p->x + xo) / 64)] == 0)
		p->x += p->dx;
	if (m->map[(int)((p->y + yo) / 64 * m->width + p->x /64)] == 0)
		p->y += p->dy;
	
}*/

void	movement(int keycode, t_player *p, t_map *m)
{
	//collision(p,m);
	(void)m;
	if (keycode == 'w')
	{
		p->x += p->dx;
		p->y += p->dy;
	}
	if (keycode == 's')
	{
		p->x -= p->dx;
		p->y -= p->dy;
	}
	if (keycode == 'a')
	{
		p->x += 5 * cos(-M_PI / 2 + p->a);
		p->y += 5 * sin(-M_PI / 2 + p->a);
	}
	if (keycode == 'd')
	{
		p->x += 5 * cos(M_PI / 2 + p->a);
		p->y += 5 * sin(M_PI / 2 + p->a);
	}
}
