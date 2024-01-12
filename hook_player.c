/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:43:49 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/12 16:41:00 by hlasota          ###   ########.fr       */
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

void	collision(int keycode, t_player *p, t_map *m)
{
	int xo;
	int yo;

	if (p->dx < 0)
		xo = -25;
	else
		xo = 25;
	if (p->dy < 0)
		yo = -25;
	else
		yo = 25;
	if (keycode == 's')
	{
		if (m->map[(int)(p->y / 64) * m->width + (int)((p->x - xo) / 64)] != '1')
			p->x -= p->dx * 1.3;
		if (m->map[(int)((p->y - yo) / 64) * m->width + (int)(p->x / 64)] != '1')
			p->y -= p->dy * 1.3;
	}
	if (keycode == 'w')
	{
		if (m->map[(int)(p->y / 64) * m->width + (int)((p->x + xo) / 64)] != '1')
			p->x += p->dx * 1.3;
		if (m->map[(int)((p->y + yo) / 64) * m->width + (int)(p->x / 64)] != '1')
			p->y += p->dy * 1.3;
	}
}

void left_side(t_player *p, t_map *m, int yo, int xo)
{
	if (fmod(p->a,(2 * M_PI)) > 3 * M_PI / 2 || (fmod(p->a,(2 * M_PI)) >  M_PI / 2 && fmod(p->a,(2 * M_PI)) < M_PI))
	{
		if (m->map[(int)(p->y / 64) * m->width + (int)((p->x - xo) / 64)]
			!= '1')
			p->x += 5 * cos(-M_PI / 2 + p->a);
		if (m->map[(int)((p->y + yo) / 64) * m->width + (int)(p->x / 64)]
			!= '1')
			p->y += 5 * sin(-M_PI / 2 + p->a);
	}
	else
	{
		if (m->map[(int)(p->y / 64) * m->width + (int)((p->x + xo) / 64)]
			!= '1')
			p->x += 5 * cos(-M_PI / 2 + p->a);
		if (m->map[(int)((p->y - yo) / 64) * m->width + (int)(p->x / 64)]
			!= '1')
			p->y += 5 * sin(-M_PI / 2 + p->a);
	}
}

void	right_side(t_player *p, t_map *m, int yo, int xo)
{
	if (fmod(p->a,(2 * M_PI)) < M_PI / 2 || ( fmod(p->a,(2 * M_PI)) > M_PI && fmod(p->a,(2 * M_PI)) < 3 * M_PI / 2))
	{
		if (m->map[(int)(p->y / 64) * m->width + (int)((p->x - xo) / 64)] != '1')
			p->x += 5 * cos(M_PI / 2 + p->a);
		if (m->map[(int)((p->y + yo) / 64) * m->width + (int)(p->x / 64)] != '1')
			p->y += 5 * sin(M_PI / 2 + p->a);
	}
	else
	{
		if (m->map[(int)(p->y / 64) * m->width + (int)((p->x + xo) / 64)] != '1')
			p->x += 5 * cos(M_PI / 2 + p->a);
		if (m->map[(int)((p->y - yo) / 64) * m->width + (int)(p->x / 64)] != '1')
			p->y += 5 * sin(M_PI / 2 + p->a);
	}
}

void	collision_side(int keycode, t_player *p, t_map *m)
{
	int xo;
	int yo;

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
		printf("rg\n");
		left_side(p, m, yo, xo);
	}
	if (keycode == 'd')
		right_side(p,m, yo, xo);
}

int	offset(int keycode, t_map *m)
{
	int i;

	i = 0;
	if (keycode == 65362)
	{
		i += 5;
		if (i + m->off >= 180)
			i = 0;
	}
	if (keycode == 65364)
	{
		i -= 5;
		if (i + m->off <= -180)
			i = 0;
	}
	return (i);
}

int	ft_strcpy(char *dst, char *src)
{
	int	i;
	i = 0;
	while ((src[i] != '\0'))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

char	*open_door(t_player *p, t_map *m, char *str, int xo, int yo)
{
	printf("%f\n", p->a);
	if (((int)(p->y / 64) * m->width + (int)((p->x + xo) / 64)) % m->width != 0
			&& ((int)(p->y / 64) * m->width + (int)((p->x + xo) / 64))
			% m->width != m->width - 1 && ((int)((p->y + yo) / 64) * m->width
			+ (int)(p->x / 64)) / m->width != 0 && ((int)((p->y + yo) / 64)
			* m->width + (int)(p->x / 64)) / m->width != m->height - 1)
	{
		if (str[(int)(p->y / 64) * m->width + (int)((p->x + xo) / 64)] == '1'
			&& (p->a > 3 * M_PI / 2 + M_PI / 4 || p->a < M_PI / 4
				|| (p->a > M_PI / 2 + M_PI / 4 && p->a < M_PI + M_PI / 4)))
		{
			printf("f\n");
			str[(int)(p->y / 64) * m->width + (int)((p->x + xo) / 64)] = '-';
		}
		
		else if(str[(int)((p->y + yo) / 64) * m->width + (int)(p->x / 64)] == '1')
			str[(int)((p->y + yo) / 64) * m->width + (int)(p->x / 64)] = '-';
	}
	return (str);
}

char	*close_door(t_player *p, t_map *m, char *str, int xo, int yo)
{
	if (p->a > 3 * M_PI / 2 + M_PI / 4 || p->a < M_PI / 4
		|| (p->a > M_PI / 2 + M_PI / 4 && p->a < M_PI + M_PI / 4))
		str[(int)(p->y / 64) * m->width + (int)((p->x + xo) / 64)] = '1';
	else if (str[(int)((p->y + yo) / 64) * m->width + (int)(p->x / 64)] != '1')
		str[(int)((p->y + yo) / 64) * m->width + (int)(p->x / 64)] = '1';
	return (str);
}
char	*door(int keycode, t_player *p, t_map *m)
{
	char	*str;
	int		xo;
	int		yo;

	if (p->dx < 0)
		xo = -64;
	else
		xo = 64;
	if (p->dy < 0)
		yo = -64;
	else
		yo = 64;
	str = malloc(ft_strlen(m->map) + 1);
	if (str == 0)
	{
		printf("erreur malloc\n");
		exit(-1);
	}
	ft_strcpy(str, m->map);
	if (keycode == 'e')
		str = open_door(p, m, str, xo, yo);
	if (keycode == 'q')
		str = close_door(p, m, str, xo, yo);
	return (str);
}

void	finish(t_all *a)
{
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
	//char *temp_door;

	if (keycode == 65307)
		finish(a);
	a->m->off += offset(keycode, a->m);
	collision(keycode, a->p, a->m);
	collision_side(keycode, a->p, a->m);
	/*temp_door =	door(keycode, a->p, a->m);
	a->m->map = temp_door;
	free(temp_door);*/
	a->m->map = door(keycode, a->p, a->m);
}
