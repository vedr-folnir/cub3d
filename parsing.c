/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 07:43:37 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/29 09:48:11 by hlasota          ###   ########.fr       */
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

void	verif_map(t_all *a)
{
	int	i;

	i = 0;
	while (a->m->map[i] == ' ' || a->m->map[i] == '	')
	{
		a->m->map[i++] = '1';
	}
	if (a->m->map[i] != '1')
	{
		printf("Error\n Error map");
		finish(a);
	}
	while (a->m->map[i])
	{
		if (a->m->map[i] != '0' && a->m->map[i] != '1' && a->m->map[i] != 'N'
			&& a->m->map[i] != 'S' && a->m->map[i] != 'E' && a->m->map[i] != 'W'
			&& a->m->map[i] != '-')
		{
			printf("Error\n Error map");
			finish(a);
		}
		i++;
	}
}

t_map	*aff_map(t_map *m)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (m->map[i++])
		if ((m->map[i] == 'N' || m->map[i] == 'S' || m->map[i] == 'E'
				|| m->map[i] == 'W'))
			j++;
	if (j != 1)
	{
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
		err(6);
	}
	return (m);
}

void	parsing(t_map *m, char *path)
{
	int	fd;

	fd = get_fd(path);
	m = parse_texture(m, fd);
	m->map_t[0] = get_next_line(fd);
	m = parsing_map(m, fd);
	if (m->flag_error != 0)
	{
		free(m->map);
		if (m->so != 0)
			free(m->so);
		if (m->no != 0)
			free(m->no);
		if (m->ea != 0)
			free(m->ea);
		if (m->we != 0)
			free(m->we);
	}
	m->map_t = same_size(m);
	verif_space(m);
	m = signle_char(m);
	m = aff_map(m);
}
