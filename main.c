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

void GiveRainbowColor(double position, t_env *env)
{
  /* if position > 1 then we have repetition of colors it maybe useful    */
	t_color c;

	if (position > 1.0)
	{
		if (position - (int)position == 0.0)position = 1.0;
		else position = position - (int)position;
	}
 
  unsigned char nmax = 6; /* number of color segments */
  double m = nmax * position;
 
  int n = (int)m; // integer of m
 
  double f = m - n;  // fraction of m
  unsigned char t = (int)(f * 255);

	if (n == 0)
		c = ft_rgb_to_color(255, t, 0);
	else if (n == 1)
		c = ft_rgb_to_color(255 - t, 255, 0);
	else if (n == 2)
		c = ft_rgb_to_color(0, 255, t);
	else if (n == 3)
		c = ft_rgb_to_color(0, 255 - t, 255);
	else if (n == 4)
		c = ft_rgb_to_color(t, 0, 255);
	else if (n == 5)
		c = ft_rgb_to_color(255, 0, 255 - t);
	else
		c = ft_rgb_to_color(0, 0, 0);

	env->img.clrline = ft_color_to_int(c);

}

void	mandelbrot(t_env *env)
{
	int x;
	int y;
	float x1 = - 2.1;
	float x2 = 0.6;
	float y1 = - 1.2;
	float y2 = 1.2;
	int ite_max = 25;
	int image_x = (x2 - x1) * env->zoom;
	int image_y = (y2 - y1) * env->zoom;
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
			c_r = (float)(x + env->xoff) / (float)env->zoom + (float)x1;
			c_i = (float)(y + env->yoff) / (float)env->zoom + (float)y1;
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
			GiveRainbowColor((double)i / (double)ite_max, env);
			// if (i == ite_max)
				ft_put_pixel_img(ft_new_point(x, y), env->img);
			y++;
		}
		x++;
	}
}

void	var_init(t_env *env)
{
	env->zoom = 300;
	env->re = 1;
	env->xoff = 0;
	env->yoff = 0;
}

int 	keyhook(int keycode, t_env *env)
{
	env = env;

	if (keycode == 65307)
		exit(0);
	if (keycode == 65451)
		env->zoom += 10, env->re = 1;
	if (keycode == 65453)
		env->zoom -= 10, env->re = 1;
	// printf("%d\n", keycode);
	return (0);
}

int 	mousehook(int button, int x, int y, t_env *env)
{
	env = env;

	if (button == 4)
	{
		env->zoom += 10;
		env->xoff += (x - (SIZE_WIN_X / 2));
		env->yoff += (y - (SIZE_WIN_Y / 2));
		env->re = 1;
	}
	if (button == 5)
		env->zoom -= 10, env->re = 1;
	printf("x = %d, y = %d, button = %d\n", x, y, button);
	return (0);
}

int		loophook(t_env *env)
{
	if (env->re == 1)
	{
		ft_bzero(env->img.data, 4 * SIZE_WIN_X * SIZE_WIN_Y);
		mandelbrot(env);
		env->re = 0;
		mlx_put_image_to_window(env->mlx, env->win, env->img.img, 0, 0);
	}

	return (0);
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
	var_init(&env);
	//mandelbrot(&env);
	mlx_key_hook(env.win, keyhook, &env);
	mlx_mouse_hook(env.win, mousehook, &env);
	mlx_loop_hook(env.mlx, loophook, &env);
	mlx_loop(env.mlx);
	return (0);
}
