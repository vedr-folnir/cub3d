/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 14:22:01 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/29 10:30:10 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./cub3D.h"

char	*get_texture(int fd, int letter)
{
	char	*line;
	char	letters[2];
	int		i;

	letters[0] = 'F';
	letters[1] = 'C';
	line = get_next_line(fd);
	while (ft_strlen(line) == 1)
	{
		free(line);
		line = get_next_line(fd);
	}
	i = 0;
	while (line[i] == ' ' || line[i] == '	')
		i++;
	if (letters[letter] != line[i])
		err(8);
	return (line);
}

int	ft_size_tab_char(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	free_rgb(t_map *m, char **stack)
{
	int	i;

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
	i = 0;
	while (stack[i])
		free(stack[i++]);
	free(stack);
}

int	rgb_texture_need(char *line, t_map *m)
{
	char	**stack;
	int		i;
	int		result;

	i = 1;
	while (line[i] == ' ' || line[i] == '	')
		i++;
	line = &line[i];
	stack = ft_split(line, ',');
	if (ft_size_tab_char(stack) != 3 || ft_atoi(stack[0]) < 0
		|| ft_atoi(stack[1]) < 0 || ft_atoi(stack[2]) < 0)
	{
		free_rgb(m, stack);
		err(8);
	}
	result = ft_atoi(stack[0]) * pow(256, 2) + ft_atoi(stack[1]) * 256
		+ ft_atoi(stack[2]);
	i = 0;
	while (stack[i])
		free(stack[i++]);
	free(stack);
	return (result);
}
