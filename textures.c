/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:10:01 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/26 15:17:28 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./cub3D.h"

int	get_texture_fd(char *path, t_map *m)
{
	int	file;

	(void)m;
	path[ft_strlen(path) - 1] = 0;
	file = open(path + 3, O_RDONLY);
	return (file);
}

void	error_fd(int *pixel, t_map *m, char *line)
{
	free(pixel);
	free(m->map_t);
	free(m->map);
	free(line);
	if (m->so != 0)
		free(m->so);
	if (m->no != 0)
		free(m->no);
	if (m->ea != 0)
		free(m->ea);
	if (m->we != 0)
		free(m->we);
	err(8);
}

int	*texture(char *path, t_map *m, char *line)
{
	int		fd;
	char	**stack;
	int		i;
	int		*pixel;

	pixel = malloc(sizeof(int) * 3072);
	fd = get_texture_fd(path, m);
	if (fd == -1)
		error_fd(pixel, m, line);
	line = get_next_line(fd);
	stack = ft_split(line, ',');
	i = 0;
	free(line);
	while (stack[i])
	{
		pixel[i] = atoi(stack[i]);
		i++;
	}
	i = 0;
	while (stack[i])
		free(stack[i++]);
	free(stack);
	return (pixel);
}

t_map	*inside_texture(t_map *m, char *line, int i)
{
	if (ft_strncmp(&line[i], "SO ", 3) == 0 && m->so == 0)
		m->so = texture(&line[i], m, line);
	else if (ft_strncmp(&line[i], "NO ", 3) == 0 && m->no == 0)
		m->no = texture(&line[i], m, line);
	else if (ft_strncmp(&line[i], "WE ", 3) == 0 && m->we == 0)
		m->we = texture(&line[i], m, line);
	else if (ft_strncmp(&line[i], "EA ", 3) == 0 && m->ea == 0)
		m->ea = texture(&line[i], m, line);
	else if (ft_strncmp(&line[i], "F", 1) == 0 && m->f == -1)
		m->f = rgb_texture_need(line, m);
	else if (ft_strncmp(&line[i], "C", 1) == 0 && m->c == -1)
		m->c = rgb_texture_need(line, m);
	else if (ft_strlen(&line[i]) != 1)
	{
		free(line);
		err(8);
	}
	return (m);
}

t_map	*parse_texture(t_map *m, int fd)
{
	char	*line;
	int		i;

	line = get_next_line(fd);
	while (line[0] != 1 && (m->no == 0 || m->so == 0 || m->ea == 0
			|| m->we == 0 || m->f == -1 || m->c == -1))
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '	')
			i++;
		m = inside_texture(m, line, i);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (m);
}
