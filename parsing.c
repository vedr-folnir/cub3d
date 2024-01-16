/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 07:43:37 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/16 17:17:45 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

int	get_fd(const char *path)
{
	int	file;

	file = open(path, O_RDONLY);
	if (file == -1)
		err(2);
	return (file);
}

char	*verif_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '	')
	{
		line[i++] = '1';
	}
	if (line[i] != '1')
		err(4);
	while (line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == 'S'
		|| line[i] == 'E' || line[i] == 'W' || line[i] == ' ')
	{
		if (line[i] == ' ')
			line[i] = 1;
		i++;
	}
	if (line[i] != 0)
		err(5);
	return (line);
}

void	parsing(t_map *m, char *path)
{
	int	fd;
	int	i;
	int	j;

	fd = get_fd(path);
	m = parse_texture(m, fd);
	m->F = rgb_texture_need(0, fd);
	m->C = rgb_texture_need(1, fd);
	m = parsing_map(m, fd);
	m = signle_char(m);
	i = 0;
	j = 0;
	while (m->map[i])
	{
		if ((m->map[i] == 'N' || m->map[i] == 'S' || m->map[i] == 'E'
				|| m->map[i] == 'W'))
			j++;
		i++;
	}
	if (j != 1)
		err(12);
}
