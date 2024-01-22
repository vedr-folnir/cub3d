/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlasota <hlasota@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:20:50 by hlasota           #+#    #+#             */
/*   Updated: 2024/01/22 16:54:31 by hlasota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_floor_ceiling(t_all *a)
{
	int	y;
	int	x;

	y = 0;
	while (y < a->v->height)
	{
		x = 0;
		while (x != a->v->width)
		{
			if (y < a->v->height / 2 + a->m->off)
				my_mlx_pixel_put(a->d, x, y, a->m->c);
			else
				my_mlx_pixel_put(a->d, x, y, a->m->f);
			x++;
		}
		y++;
	}
}

int	hook(int keycode, t_all *a)
{
	/*int	img_width;
	int img_height;
*/
	init_img(a->v, a->d);
	angle(keycode, a->p);
	movement(keycode, a);
	draw_floor_ceiling(a);
	draw_rays(a->p, a->m, a->d);
	mlx_put_image_to_window(a->v->mlx, a->v->win, a->d->img, 0, 0);
	//a->d->img = mlx_xpm_file_to_image(a->v->mlx, "./texture/hud.xpm", &img_width, &img_height);
	//mlx_put_image_to_window(a->v->mlx, a->v->win, a->d->img, 0, 0);
	mlx_destroy_image(a->v->mlx, a->d->img);
	mini_map(a);
	printf("%f %f\n", a->p->x / 64, a->p->y / 64);
	return (1);
}

void	err(int i)
{
	printf("Error\n");
	if (i == 1)
		printf("wrong args number or map is not .cub\n");
	else if (i == 2)
		printf("border opened \n");
	else if (i == 3)
		printf("error map\n");
	else if (i == 4)
		printf("remaning space.s\n");
	else if (i == 5)
		printf("error map\n");
	else if (i == 6)
		printf("error spawn\n");
	else if (i == 7)
		printf("error malloc\n");
	else if (i == 8)
		printf("error textures\n");
	exit(i);
}

int test(t_all *a)
{
	hook(65307, a);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_vars		vars;
	t_data		img;
	t_player	player;
	t_map		map;
	t_all		a;

	if (argc != 2 || ft_strncmp((argv[1] + ft_strlen(argv[1]) - 4), ".cub", 4))
		err(1);
	init_map(&map, argv[1]);
	init_win(&vars);
	init_player(&player, &map);
	init_img(&vars, &img);
	a.flag = 0;
	a.v = &vars;
	a.p = &player;
	a.d = &img;
	a.m = &map;
	draw_floor_ceiling(&a);
	draw_rays(a.p, a.m, a.d);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_destroy_image(a.v->mlx, a.d->img);
	mlx_hook(vars.win, 17, 0, test, &a);
	mlx_hook(vars.win, 2, 1L << 0, hook, &a);
	mlx_loop(vars.mlx);
	return (0);
}
