/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:13:32 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/29 10:29:49 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./cub3D.h"

void	free_error(t_map *m)
{
	int	i;

	i = 0;
	while (i != m->height)
	{
		free(m->map_t[i++]);
	}
	free(m->map_t);
	free(m->map);
	if (m->so != 0)
		free(m->so);
	if (m->no != 0)
		free(m->no);
	if (m->ea != 0)
		free(m->ea);
	if (m->we != 0)
		free(m->we);
	err(2);
}

void	flood_fill(t_map *m, int x, int y, char *arg)
{
	if (x < 0 || x >= m->height || y < 0 || y >= m->width)
		return ;
	if (m->map_t[x][y] != arg[0])
		return ;
	if (arg[0] == '0')
		if (y == 0 || y == m->width || x == 0 || x == m->height)
			if (m->map_t[x][y] == '0')
				free_error(m);
	if (arg[0] == ' ')
		if ((x + 1 < m->height && m->map_t[x + 1][y] == '0') || (x - 1 > 0
				&& m->map_t[x - 1][y] == '0') || (y + 1 < m->width
				&& m->map_t[x][y + 1] == '0') || (y - 1 > 0 && m->map_t[x][y
				- 1] == '0'))
			return ;
	m->map_t[x][y] = arg[1];
	flood_fill(m, x + 1, y, arg);
	flood_fill(m, x - 1, y, arg);
	flood_fill(m, x, y + 1, arg);
	flood_fill(m, x, y - 1, arg);
}

void	remove_space(t_map *m)
{
	int	i;

	i = 0;
	while (i < m->height)
	{
		flood_fill(m, i, 0, " 1");
		flood_fill(m, i, m->width, " 1");
		i++;
	}
	i = 0;
	while (i <= m->width)
	{
		flood_fill(m, 0, i, " 1");
		flood_fill(m, m->height - 1, i, " 1");
		i++;
	}
}

void	verif_space(t_map *m)
{
	int		i;
	int		j;
	char	dir;

	remove_space(m);
	i = 0;
	while (i < m->height)
	{
		j = 0;
		while (j < m->width)
		{
			if (m->map_t[i][j] == 'N' || m->map_t[i][j] == 'S'
				|| m->map_t[i][j] == 'E' || m->map_t[i][j] == 'W')
			{
				dir = m->map_t[i][j];
				m->map_t[i][j] = '0';
				flood_fill(m, i, j, "0-");
				m->map_t[i][j] = dir;
			}
			j++;
		}
		i++;
	}
}
