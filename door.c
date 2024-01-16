/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 16:31:41 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/16 16:39:53 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./cub3D.h"

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

char	*open_door(t_player *p, t_map *m, char *str, int xo)
{
	int	yo;

	if (p->dy < 0)
		yo = -64;
	else
		yo = 64;
	if (((int)(p->y / 64) * m->width + (int)((p->x + xo) / 64)) % m->width != 0
			&& ((int)(p->y / 64) * m->width + (int)((p->x + xo) / 64))
			% m->width != m->width - 1 && ((int)((p->y + yo) / 64) *m->width
			+ (int)(p->x / 64)) / m->width != 0 && ((int)((p->y + yo) / 64)
			*m->width + (int)(p->x / 64)) / m->width != m->height - 1)
	{
		if (str[(int)(p->y / 64) * m->width + (int)((p->x + xo) / 64)] == '1'
			&& (p->a > 3 * M_PI / 2 + M_PI / 4 || p->a < M_PI / 4
				|| (p->a > M_PI / 2 + M_PI / 4 && p->a < M_PI + M_PI / 4)))
			str[(int)(p->y / 64) * m->width + (int)((p->x + xo) / 64)] = '-';
		else if (str[(int)((p->y + yo) / 64)
			*m->width + (int)(p->x / 64)] == '1')
			str[(int)((p->y + yo) / 64)*m->width + (int)(p->x / 64)] = '-';
	}
	return (str);
}

char	*close_door(t_player *p, t_map *m, char *str)
{
	int	xo;
	int	yo;

	if (p->dx < 0)
		xo = -64;
	else
		xo = 64;
	if (p->dy < 0)
		yo = -64;
	else
		yo = 64;
	if (p->a > 3 * M_PI / 2 + M_PI / 4 || p->a < M_PI / 4
		|| (p->a > M_PI / 2 + M_PI / 4 && p->a < M_PI + M_PI / 4))
		str[(int)(p->y / 64) * m->width + (int)((p->x + xo) / 64)] = '1';
	else if (str[(int)((p->y + yo) / 64)*m->width
		+ (int)(p->x / 64)] != '1')
		str[(int)((p->y + yo) / 64)*m->width + (int)(p->x / 64)] = '1';
	return (str);
}

char	*door(int keycode, t_player *p, t_map *m)
{
	char	*str;
	int		xo;

	if (p->dx < 0)
		xo = -64;
	else
		xo = 64;
	str = malloc(ft_strlen(m->map) + 1);
	if (str == 0)
	{
		printf("erreur malloc\n");
		exit(-1);
	}
	ft_strcpy(str, m->map);
	if (keycode == 'e')
		str = open_door(p, m, str, xo);
	if (keycode == 'q')
		str = close_door(p, m, str);
	free(m->map);
	return (str);
}
