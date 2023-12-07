/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:43:19 by hlasota           #+#    #+#             */
/*   Updated: 2023/12/07 14:03:27 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./cub3D.h"

void	init_win(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->width = 1024;
	vars->height = 512;
	vars->win = mlx_new_window(vars->mlx, vars->width, vars->height, "cub3D");
}

void	init_img(t_vars *vars, t_data *img)
{
	img->img = mlx_new_image(vars->mlx, 1024, 512);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
			&img->endian);
}

void	init_player(t_player *p)
{
	p->x = 300;
	p->y = 300;
	p->taille = 10;
	p->a = M_PI / 2; //changer par rapport a la direction du depart de la map
	p->dx = cos(p->a);
	p->dy = sin(p->a);
}

void	init_map(t_map *m, char *path)
{
	parsing(m, path);
	m->width = 15;
	m->height = 14;
	//m->width = 8;
	//m->height = 8;
	m->size = m->width * m->height;
	
	m->map ="111111111111111100100010001101100100000010001101100000000101100010000010001101000001000001101000000000001100100010001101100100000010001101100000000101100010000010001101000001000001101000000000001111111111111111";
	//m->map ="1111111110000001101000011010000110000001100001011000000111111111";
	/*m->map ="
11111111
10000001
10100001
10100001
10000001
10000101
10000001
11111111";*/
	//printf("%s\n", m->map);
}

t_all	init_all(t_all *a, t_vars *v, t_data *d, t_player *p, t_map *m)
{
	a->flag = 0;
	a->v = v;
	a->p = p;
	a->d = d;
	a->m = m;
	return (*a);
}
