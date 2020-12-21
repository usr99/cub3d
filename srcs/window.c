/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 13:02:50 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/22 00:26:34 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/window.h"

void	create_window(t_map_specs specs)
{
	t_window	win;

	if (!(win.mlx = mlx_init()))
		exit(EXIT_FAILURE);
	win.win = mlx_new_window(win.mlx, specs.width, specs.height, "CUB3D");
	if (win.win == NULL)
		exit(EXIT_FAILURE);
	win.specs = specs;
	create_floor_and_sky(&win, specs);
	get_player_info(&win, specs);

	display_window(win);
	mlx_do_key_autorepeaton(win.mlx);
	mlx_hook(win.win, 2, 1L << 0, &handle_event, &win);
	mlx_loop(win.mlx);
}

void	create_floor_and_sky(t_window *window, t_map_specs specs)
{
	t_img	sky;
	t_img	floor;
	int		i;
	int		nb_pixels_img;

	sky.img = mlx_new_image(window->mlx, specs.width, specs.height / 2);
	floor.img = mlx_new_image(window->mlx, specs.width, specs.height / 2);
	if (sky.img == NULL || floor.img == NULL)
		exit(EXIT_FAILURE);
	nb_pixels_img = specs.width * (specs.height / 2);
	sky.addr = (unsigned int *)mlx_get_data_addr(sky.img, &sky.bpp,
		&sky.size_line, &sky.endian);
	floor.addr = (unsigned int *)mlx_get_data_addr(floor.img, &floor.bpp,
		&floor.size_line, &floor.endian);
	i = -1;
	while (++i < nb_pixels_img)
		sky.addr[i] = specs.c_color;
	i = -1;
	while (++i < nb_pixels_img)
		floor.addr[i] = specs.f_color;
	window->sky = sky;
	window->floor = floor;
}

void	display_window(t_window window)
{
	int	color;
	int	line_height;
	int	x;

	x = 0;
	mlx_put_image_to_window(window.mlx, window.win, window.floor.img, 0,
		window.specs.height / 2);
	mlx_put_image_to_window(window.mlx, window.win, window.sky.img, 0, 0);
	while (x < window.specs.width)
	{
		line_height = raycast(window.player, window.specs, x, &color);
		draw_line(window, line_height, x, color);
		x++;
	}
}

void	draw_line(t_window window, int line_height, int x, int color)
{
	int	bottom;
	int	top;
	int	y;

	bottom = -line_height / 2 + window.specs.height / 2;
	if (bottom < 0)
		bottom = 0;
	top = line_height / 2 + window.specs.height / 2;
	if (top > window.specs.height)
		top = window.specs.height;
	y = bottom;
	while (y < top)
	{
		mlx_pixel_put(window.mlx, window.win, x, y, color);
		y++;
	}
}