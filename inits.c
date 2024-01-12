/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:43:19 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/12 17:10:12 by hlasota          ###   ########.fr       */
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
	img->img = mlx_new_image(vars->mlx, 1024 * 2, 512 * 2);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
			&img->endian);
}

void	init_player(t_player *p, t_map *m)
{
	int i;

	i = 0;
	while (m->map[i] != 'N' && m->map[i] != 'S'
		&& m->map[i] != 'E' && m->map[i] != 'W')
		i++;
	p->y = i / m->width * 64 + 32;
	p->x = i % m->width * 64 + 32;
	p->taille = 10;
	if (m->map[i] == 'N')
		p->a = 3 * M_PI / 2;
	else if (m->map[i] == 'S')
		p->a = M_PI / 2;
	else if (m->map[i] == 'W')
		p->a = M_PI;
	else
		p->a =0;
	p->dx = cos(p->a);
	p->dy = sin(p->a);
}


void	init_map(t_map *m, char *path)
{
	m->NO = 0;
	m->SO = 0;
	m->WE = 0;
	m->EA = 0;
	m->map = "\0";
	m->width = 0;
	m->height = 0;
	parsing(m, path);
	//test_map();
	//m->width = 15;
	//m->height = 14;
	m->off = 0;
	//m->width = 8;
	//m->height = 8;
	m->size = m->width * m->height;
	int i = 0;

	//m->map ="1111111111111111--1---1---11-11--1------1---11-11---N----1-11---1-----1---11-1-----1-----11-1-----------11--1---1---11-11--1------1---11-11--------1-11---1-----1---11-1-----1-----11-1-----------1111111111111111";
	while (m->map[i])
	{
		printf("%c", m->map[i]);
		if ((i+1) % ( m->width) == 0 && i != 0)
			printf("\n");
		i++;
	}
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
