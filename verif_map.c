/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:16:33 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/29 10:05:16 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"

char	*ft_one(char *in, char *out, int n)
{
	int	i;

	i = 0;
	while (in[i])
	{
		out[i] = in[i];
		i++;
	}
	while (i < n)
		out[i++] = ' ';
	out[i++] = 0;
	return (out);
}

char	**same_size(t_map *m)
{
	char	**tab;
	int		i;

	tab = (char **)malloc(m->height * sizeof(char *));
	if (!tab)
		err(7);
	i = 0;
	while (i < m->height)
	{
		tab[i] = (char *)malloc((m->width) * sizeof(char));
		if (!tab[i])
			err(7);
		tab[i] = ft_one(m->map_t[i], tab[i], m->width);
		free(m->map_t[i]);
		i++;
	}
	free(m->map_t);
	return (tab);
}

t_map	*parsing_map(t_map *m, int fd)
{
	int	i;
	int	len;

	if (m->map_t[0] == 0)
		m->flag_error = 1;
	while (m->flag_error == 0 && ft_strlen(m->map_t[0]) == 1)
	{
		free(m->map_t[0]);
		m->map_t[0] = get_next_line(fd);
	}
	i = 0;
	while (m->flag_error == 0 && m->map_t[i])
	{
		len = ft_strlen(m->map_t[i]);
		if (m->map_t[i][len - 1] == '\n')
			m->map_t[i][len - 1] = 0;
		if (len > m->width)
			m->width = len;
		m->height++;
		i++;
		m->map_t[i] = get_next_line(fd);
	}
	m->map_t[i] = 0;
	return (m);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
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
	int	i;

	i = 0;
	while (i < m->height)
	{
		ft_strlcat(m->map, m->map_t[i], ft_strlen(m->map)
			+ ft_strlen(m->map_t[i]) + 1);
		free(m->map_t[i++]);
	}
	return (m);
}
