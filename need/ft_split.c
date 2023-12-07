/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 14:24:19 by hlasota           #+#    #+#             */
/*   Updated: 2023/11/29 09:38:40 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

static int	ft_count_wrd(const char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] != '\0')
			j++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (j);
}

static int	*ft_count_len_wrd(const char *str, char c)
{
	int	i;
	int	k;
	int	m;
	int	*result;

	i = 0;
	m = 0;
	result = (int *)malloc(sizeof(int) * (ft_count_wrd(str, c)));
	if (!result)
		return (NULL);
	while (str[i])
	{
		k = 0;
		while (str[i] && str[i] == c)
			i++;
		while (str[i] && str[i] != c)
		{
			k++;
			i++;
		}
		if (k > 0)
			result[m++] = k;
	}
	return (result);
}

static char	*ft_strcpy(char *dest, const char *str, int start, int end)
{
	int	i;

	i = 0;
	while (str[start] != '\0' && start != end)
	{
		dest[i] = str[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_piece_2(char **dst, int *lw, const char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
		{
			dst[j] = (char *)malloc(sizeof(char) * (lw[j] + 1));
			ft_strcpy(dst[j], str, i, (i + lw[j]));
			i = i + lw[j];
			j++;
		}
	}
	dst[j] = NULL;
	return (dst);
}

char	**ft_split(const char *str, char c)
{
	int		word;
	int		*lw;
	char	**dst;

	word = ft_count_wrd(str, c);
	lw = ft_count_len_wrd(str, c);
	dst = (char **)malloc(sizeof(char *) * (word + 1));
	if (!dst)
		return (NULL);
	ft_piece_2(dst, lw, str, c);
	free(lw);
	return (dst);
}
