/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:27:42 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/26 11:42:06 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

t_ray	angle_is_zero(t_player *p, t_ray *ray)
{
	ray->rx = p->x;
	ray->ry = p->y;
	ray->dof = 1000;
	return (*ray);
}

t_ray	while_hori(t_ray ray, t_player *p, t_map *m)
{
	ray.mx = (int)(ray.rx) >> 6;
	ray.my = (int)(ray.ry) >> 6;
	ray.mp = ray.my * m->width + ray.mx;
	if (ray.mp > 0 && ray.mp < m->size && m->map[ray.mp] == '1')
	{
		ray.type = m->map[ray.mp];
		ray.hx = ray.rx;
		ray.hy = ray.ry;
		ray.dist_h = sqrt(pow(ray.hy - p->y, 2) + pow(ray.hx - p->x, 2));
		ray.dof = ray.max_dof;
	}
	else
	{
		ray.rx += ray.xo;
		ray.ry += ray.yo;
		ray.dof += 1;
	}
	return (ray);
}

t_ray	check_hori(t_ray ray, t_player *p, t_map *m)
{
	ray.dof = 0;
	ray.dist_h = 10000000;
	ray.hx = p->x;
	ray.hy = p->y;
	ray.atan = -1 / tan(ray.ra);
	if (ray.ra > M_PI)
	{
		ray.ry = (((int)p->y >> 6) << 6) - 0.0001;
		ray.rx = (p->y - ray.ry) * ray.atan + p->x;
		ray.yo = -64;
		ray.xo = -ray.yo * ray.atan;
	}
	if (ray.ra < M_PI)
	{
		ray.ry = (((int)p->y >> 6) << 6) + 64;
		ray.rx = (p->y - ray.ry) * ray.atan + p->x;
		ray.yo = 64;
		ray.xo = -ray.yo * ray.atan;
	}
	if (ray.ra == 0 || ray.ra == M_PI)
		ray = angle_is_zero(p, &ray);
	while (ray.dof < ray.max_dof)
		ray = while_hori(ray, p, m);
	return (ray);
}

t_ray	while_vert(t_ray ray, t_player *p, t_map *m)
{
	ray.mx = (int)(ray.rx) >> 6;
	ray.my = (int)(ray.ry) >> 6;
	ray.mp = ray.my * m->width + ray.mx;
	if (ray.mp > 0 && ray.mp < m->size && m->map[ray.mp] == '1')
	{
		ray.type = m->map[ray.mp];
		ray.vx = ray.rx;
		ray.vy = ray.ry;
		ray.dist_v = sqrt(pow(ray.ry - p->y, 2) + pow(ray.rx - p->x, 2));
		ray.dof = ray.max_dof;
	}
	else
	{
		ray.rx += ray.xo;
		ray.ry += ray.yo;
		ray.dof++;
	}
	return (ray);
}

t_ray	check_vert(t_ray ray, t_player *p, t_map *m)
{
	ray.dof = 0;
	ray.dist_v = 10000000;
	ray.vx = p->x;
	ray.vy = p->y;
	ray.atan = -tan(ray.ra);
	if (ray.ra > M_PI / 2 && ray.ra < 3 * M_PI / 2)
	{
		ray.rx = (((int)p->x >> 6) << 6) - 0.0001;
		ray.ry = (p->x - ray.rx) * ray.atan + p->y;
		ray.xo = -64;
		ray.yo = -ray.xo * ray.atan;
	}
	if (ray.ra < M_PI / 2 || ray.ra > 3 * M_PI / 2)
	{
		ray.rx = (((int)p->x >> 6) << 6) + 64;
		ray.ry = (p->x - ray.rx) * ray.atan + p->y;
		ray.xo = 64;
		ray.yo = -ray.xo * ray.atan;
	}
	if (ray.ra == 0 || ray.ra == M_PI)
		ray = angle_is_zero(p, &ray);
	while (ray.dof < ray.max_dof)
		ray = while_vert(ray, p, m);
	return (ray);
}
