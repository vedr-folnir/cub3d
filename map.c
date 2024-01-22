/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:57:52 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/22 13:15:07 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

void	mini_map(t_all *a)
{
	int	i;
	int	x;
	int	y;

	system("clear");
	x = (int)a->p->x / 64;
	y = (int)a->p->y / 64;
	a->m->map[y * a->m->width + x] = 'P';
	i = 0;
	while (a->m->map[i])
	{
		if (a->m->map[i] == 'P')
			printf("\033[1;36m%c\033[0m", a->m->map[i]);
		else if (a->m->map[i] == '.')
			printf("\033[1;32m%c\033[0m", a->m->map[i]);
		else
			printf("%c", a->m->map[i]);
		if ((i + 1) % (a->m->width) == 0 && i != 0)
			printf("\n");
		i++;
	}
	a->m->map[y * a->m->width + x] = '.';
}

/*
void	draw_line_player(t_player *p, t_data *d, unsigned int color)
{
	double	delta_x;
	double	delta_y;
	int		pixels;
	double	pixel_x;
	double	pixel_y;

	(void)color;
	pixel_x = p->x;
	pixel_y = p->y;
	delta_y = (p->y + p->dy * 7) - p->y;
	delta_x = (p->x + p->dx * 7) - p->x;
	pixels = sqrt(delta_x * delta_x + delta_y * delta_y);
	delta_x /= pixels;
	delta_y /= pixels;
	while (pixels)
	{
		if (pixel_y < 0)
			break ;
		if (pixel_x > -1)
			my_mlx_pixel_put(d, (int)pixel_x + 5, (int)pixel_y + 5, 0xff0000);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--pixels;
	}
}*/
