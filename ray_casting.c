/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:21:08 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/30 13:09:40 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./cub3D.h"

t_ray	draw_rays_calc(t_ray ray, t_player *p, t_map *m)
{
	ray.max_dof = m->height;
	if (m->width > m->height)
		ray.max_dof = m->width;
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
	return (ray);
}

t_ray	draw_rays_3d(t_ray ray, t_player *p, t_map *m)
{
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
	return (ray);
}

void	draw_rays_texture(t_ray ray, t_data *d, t_map *m, int y)
{
	if (ray.shade == 0.5 && (ray.ra > 3 * M_PI / 2 || ray.ra < M_PI
			/ 2))
		my_mlx_pixel_put(d, ray.nb_r, y + ray.line_o + m->off,
			pow(256, 2) * m->ea[ray.pixel] + 256
			* m->ea[ray.pixel + 1] + m->ea[ray.pixel + 2]);
	else if (ray.shade == 0.5 && (ray.ra < 3 * M_PI / 2
			|| ray.ra > M_PI / 2))
		my_mlx_pixel_put(d, ray.nb_r, y + ray.line_o + m->off,
			pow(256, 2) * m->we[ray.pixel] + 256
			* m->we[ray.pixel + 1] + m->we[ray.pixel + 2]);
	else if (ray.shade == 1 && ray.ra > 0 && ray.ra < M_PI)
		my_mlx_pixel_put(d, ray.nb_r, y + ray.line_o + m->off,
			pow(256, 2) * m->so[ray.pixel] + 256
			* m->so[ray.pixel + 1] + m->so[ray.pixel + 2]);
	else if (ray.shade == 1 && ray.ra > M_PI)
		my_mlx_pixel_put(d, ray.nb_r, y + ray.line_o + m->off,
			pow(256, 2) * m->no[ray.pixel] + 256
			* m->no[ray.pixel + 1] + m->no[ray.pixel + 2]);
}

t_ray	draw_rays_wall(t_ray ray, t_data *d, t_map *m)
{
	int	y;

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
			draw_rays_texture(ray, d, m, y);
		y++;
		ray.ty += 32 / (float)ray.line_h;
	}
	return (ray);
}

void	draw_rays(t_player *p, t_map *m, t_data *d)
{
	t_ray	ray;

	ray.ra = p->a - 0.0174533 * 30;
	ray.nb_r = -1;
	while (ray.nb_r <= 1022)
	{
		ray = draw_rays_calc(ray, p, m);
		ray = draw_rays_3d(ray, p, m);
		ray = draw_rays_wall(ray, d, m);
		ray.ra = ray.ra + 0.0174533 / 16;
		if (ray.ra < 0)
			ray.ra += 2 * M_PI;
		if (ray.ra > 2 * M_PI)
			ray.ra -= 2 * M_PI;
	}
}
