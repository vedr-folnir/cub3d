/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 07:43:37 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/16 13:08:18 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

void floodFill(t_map *m, int x, int y, char old, char new)
{
	if (x < 0 || x >= m->height || y < 0 || y >= m->width)
		return ;
	if (m->map_t[x][y] != old)
		return ;
	if (old == '0')
		if (y == 0 || y == m->width || x == 0 || x == m->height)
			if (m->map_t[x][y] == '0')
				err(2);
	if (old == ' ')
		if ((x + 1 < m->height && m->map_t[x + 1][y] == '0')
			|| (x - 1 > 0 && m->map_t[x - 1][y] == '0')
			|| (y + 1 < m->width && m->map_t[x][y + 1] == '0')
			|| (y - 1 > 0 && m->map_t[x][y - 1] == '0'))
				return ;
	m->map_t[x][y] = new;
	floodFill(m, x + 1, y, old, new);
	floodFill(m, x - 1, y, old, new);
	floodFill(m, x, y + 1, old, new);
	floodFill(m, x, y - 1, old, new);
}

void remove_space(t_map *m)
{
	int i;

	i = 0;
	while (i < m->height)
	{
		floodFill(m, i, 0, ' ', '1');
		floodFill(m, i, m->width, ' ', '1');
		i++;
	}
	i=0;
	while (i <= m->width)
	{
		floodFill(m, 0, i, ' ', '1');
		floodFill(m, m->height - 1, i, ' ', '1');
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
			if (m->map_t[i][j] == ' ')
				err(4);
			if (m->map_t[i][j] == 'N' || m->map_t[i][j] == 'S'
				|| m->map_t[i][j] == 'E' || m->map_t[i][j] == 'W')
			{
				dir = m->map_t[i][j];
				m->map_t[i][j] = '0';
				floodFill(m, i, j, '0', '-');
				m->map_t[i][j] = dir;
			}
			j++;
		}
		i++;
	}
}
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
	{
		line = get_next_line(fd);
	}
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
	while (line[i] == '0' || line[i] == '1' || line[i] == 'N'
		|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W' || line[i] == ' ')
	{
		if (line[i] == ' ')
			line[i] = 1;
		i++;
	}
	if (line[i] != 0)
		err(5);
	//if (line[i - 1] != '1')
	//	err(6);
	return (line);
}

t_map	*rgb_texture( t_map *m, int fd)
{
	char	**stack;
	char	*line;

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
	return (m);
}

t_map	*parse_texture(t_map *m, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line[0] != 1 && (m->NO == 0 || m->SO == 0
			|| m->EA == 0 || m->WE == 0))
	{
		if (ft_strncmp(line, "SO ", 3) == 0 && m->SO == 0)
			m->SO = texture(line);
		else if (ft_strncmp(line, "NO ", 3) == 0 && m->NO == 0)
			m->NO = texture(line);
		else if (ft_strncmp(line, "WE ", 3) == 0 && m->WE == 0)
			m->WE = texture(line);
		else if (ft_strncmp(line, "EA ", 3) == 0 && m->EA == 0)
			m->EA = texture(line);
		else if (ft_strlen(line) == 1)
		{
			line = get_next_line(fd);
			continue ;
		}
		else
			err(3);
		line = get_next_line(fd);
	}
	return (m);
}

char	*ft_one(char *in, char *out, int n)
{
	int		i;

	i = 0;
	while (in[i])
	{
		out[i] = in[i];
		i++;
	}
	while (i < n)
		out[i++] = '1';
	out[i++] = 0;
	return (out);
}

char	**same_size(t_map *m)
{
	char **tab;
	int i;

	tab =  (char**)malloc(m->height * sizeof(char*));
	if (!tab)
		err(10);
	i = 0;
	while (i < m->height)
	{
		tab[i] =  (char*)malloc((m->width) * sizeof(char));
		if (!tab[i])
			err(11);
		tab[i] = ft_one(m->map_t[i], tab[i], m->width);
		i++;
	}
	free(m->map_t);
	return (tab);
}

t_map	*parsing_map(t_map *m, int fd)
{
	int i;
	char *line;

	line = get_next_line(fd);
	m->map_t[0] = 0;
	while (ft_strlen(line) == 1)
		line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		m->map_t[i] = line;
		if (ft_strlen(line) > m->width)
			m->width = ft_strlen(line);
		m->height++;
		//free(line);
		line = get_next_line(fd);
		i++;
	}
	m->map_t = same_size(m);
	verif_space(m);
	return (m);
}

int	ft_strlcat(char *dst, const char *src, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("r%d", j);
	while (dst[j] && j < size)
		j++;
	while (src[i] && size && (i + j) < size - 1)
	{
		dst[i + j] = src[i];
		i++;
	}
	if (j < size)
		dst[i + j] = '\0';
	i = 0;
	while (src[i])
		i++;
	return (i + j);
}

t_map	*signle_char(t_map *m)
{
	int		i;

	i = 0;
	m->map = "\0";
	while (i < m->height)
	{
		//temp = ft_strjoin(m->map, m->map_t[i]);
		//m->map = temp;//ft_strjoin(m->map, m->map_t[i++]);
		printf("fr\n");
		ft_strlcat(m->map, m->map_t[i], ft_strlen(m->map_t[i]));
		//free(m->map_t[i++]);
	}
	return (m);
}

void	parsing(t_map *m, char *path)
{
	int		fd;
	int		i;
	int		j;

	fd = get_fd(path);
	m = parse_texture(m, fd);
	m = rgb_texture(m, fd);
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
