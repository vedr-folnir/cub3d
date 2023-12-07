/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 07:43:37 by hlasota           #+#    #+#             */
/*   Updated: 2023/12/01 14:08:25 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

int	get_fd(const char *path)
{
	int		file;

	file = open(path, O_RDONLY);
	if (file == -1)
		err(2);
	return (file);
}

int	get_texture_fd(char *path)
{
	int		file;

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
	while (stack[i])
	{
		pixel[i] = atoi(stack[i]);
		i++;
	}
	return (pixel);
}

char	*get_texture(int fd, int letter)
{
	char	*line;
	char	letters[12];

	letters[0] = 'N';
	letters[1] = 'S';
	letters[2] = 'W';
	letters[3] = 'E';
	letters[4] = 'F';
	letters[5] = 'C';
	letters[6] = 'O';
	letters[7] = 'O';
	letters[8] = 'E';
	letters[9] = 'A';
	letters[10] = ' ';
	letters[11] = ' ';
	line = get_next_line(fd);
	while (ft_strlen(line) == 1)
		line = get_next_line(fd);
	//printf("%s\n", line);
	if (line[0] != letters[letter] && line[1] != letters[letter + 6])
		err(3);
	return (line);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	*result;

	i = 0;
	j = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
		return (NULL);
	while (s1[i] != '\0' && s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0' && s2[j] != '\0')
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}

void	parsing(t_map *m, char *path)
{
	int		fd;
	char	*line;
	char	**stack;
	char	**temp_map;
	int		i;

	fd = get_fd(path);
	m->NO = texture(get_texture(fd, 0));
	m->SO = texture(get_texture(fd, 1));
	m->WE = texture(get_texture(fd, 2));
	m->EA = texture(get_texture(fd, 3));
	line = get_texture(fd, 4);
	line = &line[2];
	stack = ft_split(line, ',');
	m->F = ft_atoi(stack[0]) * pow(256, 2) + ft_atoi(stack[1])
		* 256 + ft_atoi(stack[2]);
	line = get_texture(fd, 5);
	line = &line[2];
	stack = ft_split(line, ',');
	m->C = ft_atoi(stack[0]) * pow(256, 2) + ft_atoi(stack[1])
		* 256 + ft_atoi(stack[2]);
	line = get_next_line(fd);
	temp_map = malloc(1000 * sizeof(char*));
	temp_map[0] = 0;
	while (ft_strlen(line) == 1)
		line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		temp_map[i] = line;
		line = get_next_line(fd);
		printf("%s\n", temp_map[i]);
		m->width = 0;
		//while ()
		i++;
	}
	i = -1;
	

}
