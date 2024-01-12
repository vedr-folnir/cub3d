/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:25:33 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/12 14:04:32 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx_linux/mlx.h"
# include "./gnl/get_next_line.h"
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_vars {
	int		width;
	int		height;
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_player {
	float	x;
	float	y;
	float	a;
	float	dx;
	float	dy;
	int		mouse_x;
	int		mouse_y;
	int		taille;
}				t_player;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_map
{
	int		width;
	int		height;
	int		size;
	int		off;
	char	*map;
	char	**map_t;
	int		*NO;
	int		*SO;
	int		*WE;
	int		*EA;
	int		F;
	int		C;
}				t_map;

typedef struct s_ray
{
	int		nb_r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	int		color;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	dist_t;
	float	dist_h;
	float	dist_v;
	float	hx;
	float	hy;
	float	vx;
	float	vy;
	float	atan;
	float	ca;
	float	line_h;
	float	line_o;
	float	shade;
	float	ty;
	float	tx;
	int		pixel; 
	char	type;
}				t_ray;

typedef struct s_all
{
	int			flag;
	t_vars		*v;
	t_player	*p;
	t_data		*d;
	t_map		*m;
}				t_all;

void	err(int i);
void	init_win(t_vars *vars);
void	init_img(t_vars *vars, t_data *img);
void	init_player(t_player *p, t_map *m);
t_all	init_all(t_all *a, t_vars *v, t_data *d, t_player *p, t_map *m);
void	angle(int keycode, t_player *p);
void	movement(int keycode, t_all *a);
void	init_map(t_map *map, char *path);
void parsing(t_map *m, char *path);
void	draw_map(t_map *m, t_data *d);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_line_player(t_player *p, t_data *d, unsigned int color);
t_ray	angle_is_zero(t_player *p, t_ray *ray);
t_ray	while_hori(t_ray ray, t_player *p, t_map *m);
t_ray	check_hori(t_ray ray, t_player *p, t_map *m);
t_ray	while_vert(t_ray ray, t_player *p, t_map *m);
t_ray	check_vert(t_ray ray, t_player *p, t_map *m);
int		ft_strlen(char *str);
int		ft_atoi(const char *str);
char	**ft_split(const char *str, char c);
int	ft_strncmp(const char *s1, const char *s2, int n);


#endif