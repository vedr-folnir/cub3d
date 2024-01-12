/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:20:50 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/12 17:06:20 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	//printf("%d %d\n", x, y);
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_rays(t_player *p, t_map *m, t_data *d)
{
	t_ray	ray;
	int		y;
	
	ray.ra = p->a - 0.0174533 * 30;
	ray.nb_r = -1;
	while (ray.nb_r <= 1016)
	{
		ray = check_hori(ray, p, m);
		ray = check_vert(ray, p, m);
		ray.shade = 1;
		if (ray.dist_v < ray.dist_h)
		{
			ray.shade = 0.5;
			ray.rx = ray.vx;
			ray.ry = ray.vy;
			ray.dist_t = ray.dist_v;
			ray.color = 24 * pow(256, 2) + 20 * 256 + 37;
		}
		if (ray.dist_v > ray.dist_h)
		{
			ray.rx = ray.hx;
			ray.ry = ray.hy;
			ray.dist_t = ray.dist_h;
			ray.color = 0x00ff00;
		}
		ray.nb_r++;
		//---draw 3d---//
		ray.ca = p->a - ray.ra;
		if (ray.ra < 0)
			ray.ra += 2 * M_PI;
		if (ray.ra > 2 * M_PI)
			ray.ra -= 2 * M_PI;
		ray.dist_t = ray.dist_t * cos(ray.ca);
		ray.line_h = (m->size * 520) / (ray.dist_t * m->height / 3);
		if (ray.line_h > 520)
			ray.line_h = 520;
		ray.line_o = 260 - ray.line_h / 2;
		//---draw_wall---//
		ray.ty = 0;
		if (ray.shade == 1)
		{
			ray.tx = (int)(ray.rx / 2) % 32;
			if (ray.ra > M_PI)
				ray.tx = 31 - ray.tx;
		}
		else
		{
			ray.tx = (int)(ray.ry / 2) % 32;
			if (ray.ra > M_PI / 2 && ray.ra < 3 * M_PI / 2)
				ray.tx = 31 - ray.tx;
		}
		y = 0;
		while (y < ray.line_h)
		{
			ray.pixel = ((int)ray.ty * 32 + (int)ray.tx) * 3;
			
			if (y + ray.line_o + m->off >= 0)
			{	
				if (ray.shade == 0.5 && (ray.ra > 3 * M_PI / 2
					|| ray.ra <M_PI / 2))
					my_mlx_pixel_put(d, ray.nb_r, y + ray.line_o + m->off,
						pow(256,2) * m->EA[ray.pixel] + 256
						* m->EA[ray.pixel + 1]
							+ m->EA[ray.pixel + 2]);
				else if (ray.shade == 0.5 && (ray.ra < 3 * M_PI / 2
							|| ray.ra > M_PI / 2))
					my_mlx_pixel_put(d, ray.nb_r, y + ray.line_o + m->off, pow(256,
								2) * m->WE[ray.pixel] + 256 * m->WE[ray.pixel + 1]
							+ m->WE[ray.pixel + 2]);
				else if (ray.shade == 1 && ray.ra > 0 && ray.ra < M_PI)
					my_mlx_pixel_put(d, ray.nb_r, y + ray.line_o + m->off, pow(256,
									2) * m->SO[ray.pixel] + 256 * m->SO[ray.pixel + 1]
							+ m->SO[ray.pixel + 2]);
				else if (ray.shade == 1 && ray.ra > M_PI)
					my_mlx_pixel_put(d, ray.nb_r, y + ray.line_o + m->off, pow(256,
								2) * m->NO[ray.pixel] + 256 * m->NO[ray.pixel + 1]
							+ m->NO[ray.pixel + 2]);
			}
			y++;
			ray.ty += 32 / (float)ray.line_h;
		}
		ray.ra = ray.ra + 0.0174533 / 16;
		if (ray.ra < 0)
			ray.ra += 2 * M_PI;
		if (ray.ra > 2 * M_PI)
			ray.ra -= 2 * M_PI;
	}
}

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
}

void	draw_floor_ceiling(t_all *a)
{
	int	y;
	int	x;

	y = 0;
	while (y < a->v->height)
	{
		x = 0;
		while (x != a->v->width - 6)
		{
			if (y < a->v->height / 2 + a->m->off)
				my_mlx_pixel_put(a->d, x, y, a->m->C);
			else
				my_mlx_pixel_put(a->d, x, y, a->m->F);
			x++;
		}
		y++;
	}
}

int	hook(int keycode, t_all *a)
{
	printf("%f %f\n", a->p->x / 64, a->p->y / 64);
	init_img(a->v, a->d);
	angle(keycode, a->p);
	movement(keycode, a);
	draw_floor_ceiling(a);
	//draw_map(a->m, a->d);
	draw_rays(a->p, a->m, a->d);
	mlx_put_image_to_window(a->v->mlx, a->v->win, a->d->img, 0, 0);
	mlx_destroy_image(a->v->mlx, a->d->img);
	return (1);
}

void	err(int i)
{
	printf("%d\n", i);
	write(1, "Error\n", 5);
	exit(i);
}

int	main(int argc, char *argv[])
{
	t_vars vars;
	t_data img;
	t_player player;
	t_map map;
	t_all a;

	if (argc != 2 || ft_strncmp((argv[1] + ft_strlen(argv[1]) - 4), ".cub", 4))
		err(1);
	init_map(&map, argv[1]);
	init_win(&vars);
	init_img(&vars, &img);
	init_player(&player, &map);
	a = init_all(&a, &vars, &img, &player, &map);
	draw_floor_ceiling(&a);
	draw_rays(a.p, a.m, a.d);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L << 0, hook, &a);
	mlx_loop(vars.mlx);
	return (0);
}