/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eteyssed <eteyssed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 17:51:10 by eteyssed          #+#    #+#             */
/*   Updated: 2014/11/24 17:51:31 by eteyssed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"
#include <stdio.h>

t_pos	ft_new_point(int x, int y)
{
	t_pos pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

void	mandelbrot(t_env *env)
{
	int x;
	int y;
	float x1 = -2.1;
	float x2 = 0.6;
	float y1 = -1.2;
	float y2 = 1.2;
	int zoom = 600;
	int ite_max = 25;
	int image_x = (x2 - x1) * zoom;
	int image_y = (y2 - y1) * zoom;
	float c_r;
	float c_i;
	float z_r;
	float z_i;
	float tz_r;
	int i;

	x = 0;
	y = 0;
	while (x < image_x)
	{
		y = 0;
		while (y < image_y)
		{
			c_r = (float)x / (float)zoom + (float)x1;
			c_i = (float)y / (float)zoom + (float)y1;
			z_r = 0;
			z_i = 0;
			i = 0;
			while ((z_r * z_r) + (z_i * z_i) < 4 && i < ite_max)
			{
				tz_r = z_r;
				z_r = (z_r * z_r) - (z_i * z_i) + c_r;
				z_i = (2 * z_i * tz_r) + c_i;
				i++;
			}
			if (i == ite_max)
				ft_put_pixel_img(ft_new_point(x, y), env->img);
			y++;
		}
		x++;
	}
}

int		main(int ac, char **av)
{
	ac = ac;
	av = av;
	t_env env;

	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, SIZE_WIN_X, SIZE_WIN_Y, "Fract'ol");
	env.img.img = mlx_new_image(env.mlx, SIZE_WIN_X, SIZE_WIN_Y);
	env.img.data = mlx_get_data_addr(env.img.img, &env.img.bpp, &env.img.sizeline,
		&env.img.endian);
	env.img.clrline = 0xFFFFFF;
	mandelbrot(&env);
	mlx_put_image_to_window(env.mlx, env.win, env.img.img, 0, 0);
	mlx_loop(env.mlx);
	return (0);
}
