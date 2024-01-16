/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:10:01 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/16 17:10:34 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./cub3D.h"

int	get_texture_fd(char *path)
{
	int	file;

	path[ft_strlen(path) - 1] = 0;
	file = open(path + 3, O_RDONLY);
	if (file == -1)
		err(2);
	return (file);
}

int	*texture(char *path)
{
	int		fd;
	char	*line;
	char	**stack;
	int		i;
	int		*pixel;

	pixel = malloc(sizeof(int) * 3072);
	fd = get_texture_fd(path);
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

char	*get_texture(int fd, int letter)
{
	char	*line;
	char	letters[12];

	letters[0] = 'F';
	letters[1] = 'C';
	letters[2] = ' ';
	letters[3] = ' ';
	line = get_next_line(fd);
	while (ft_strlen(line) == 1)
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line[0] != letters[letter] && line[1] != letters[letter + 2])
		err(3);
	return (line);
}

int	rgb_texture_need(int val, int fd)
{
	char	**stack;
	char	*line;
	char	*temp;
	int		i;
	int		result;

	temp = "";
	temp = get_texture(fd, val);
	line = &temp[2];
	stack = ft_split(line, ',');
	result = ft_atoi(stack[0]) * pow(256, 2) + ft_atoi(stack[1]) * 256
		+ ft_atoi(stack[2]);
	free(temp);
	i = 0;
	while (stack[i])
		free(stack[i++]);
	free(stack);
	return (result);
}

t_map	*parse_texture(t_map *m, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line[0] != 1 && (m->NO == 0 || m->SO == 0 || m->EA == 0
			|| m->WE == 0))
	{
		if (ft_strncmp(line, "SO ", 3) == 0 && m->SO == 0)
			m->SO = texture(line);
		else if (ft_strncmp(line, "NO ", 3) == 0 && m->NO == 0)
			m->NO = texture(line);
		else if (ft_strncmp(line, "WE ", 3) == 0 && m->WE == 0)
			m->WE = texture(line);
		else if (ft_strncmp(line, "EA ", 3) == 0 && m->EA == 0)
			m->EA = texture(line);
		else if (ft_strlen(line) != 1)
			err(3);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (m);
}
