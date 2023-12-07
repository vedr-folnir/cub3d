/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:57:52 by hlasota           #+#    #+#             */
/*   Updated: 2023/12/04 13:59:11 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

void	draw_square(int x1, int y1, int color, t_data *d)
{
	int x;
	int y;

	y = y1;
	while (y < y1 + 64 - 1)
	{
		x = x1;
		while (x < x1 + 64 - 1)
		{
			my_mlx_pixel_put(d,  x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_map(t_map *m, t_data *d)
{
	int x;
	int y;
	(void) d;
	y = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			if (m->map[y * m->width + x] == '1')
				draw_square(x * m->size + 1, y * m->size + 1, 0xffffff, d);
			else
				draw_square(x * m->size + 1, y * m->size + 1, 0x212121, d);
			x++;
		}
		y++;
	}
}
