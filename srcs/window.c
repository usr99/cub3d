/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 13:02:50 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/23 20:02:26 by mamartin         ###   ########.fr       */
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
	create_texture(&win, specs);
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

void	create_texture(t_window *window, t_map_specs specs)
{
	t_img	tx;
	int		i;
	
	i = 0;
	while (i < 5)
	{
		tx.img = mlx_xpm_file_to_image(window->mlx, specs.texture[i],
			&tx.width, &tx.height);
		if (tx.img == NULL)
			show_error(NULL, NULL, "Bad path for texture\n");
		tx.addr = (unsigned int *)mlx_get_data_addr(tx.img, &tx.bpp,
			&tx.size_line, &tx.endian);
		window->tex[i] = tx;
		i++;
	}
	tx.img = mlx_new_image(window->mlx, specs.width, specs.height);
	if (tx.img == NULL)
		exit(EXIT_FAILURE);
	tx.addr = (unsigned int *)mlx_get_data_addr(tx.img, &tx.bpp,
		&tx.width, &tx.height);
	i = specs.width * specs.height;
	while (i--)
	{
		tx.addr[i] = 0;
		tx.addr[i] = tx.addr[i] | (255 << 24);
	}	
	window->walls = tx;
}

void	display_window(t_window window)
{
	t_wall	wall;
	int		x;

	x = 0;
	mlx_put_image_to_window(window.mlx, window.win, window.floor.img, 0,
		window.specs.height / 2);
	mlx_put_image_to_window(window.mlx, window.win, window.sky.img, 0, 0);
	//mlx_put_image_to_window(window.mlx, window.win, window.walls.img, 0, 0);
	while (x < window.specs.width)
	{
		wall = raycast(window.player, window.specs, x);
		draw_line(window, x, wall);
		x++;
	}
}

void	draw_line(t_window window, int x, t_wall wall)
{
	double	step;
	double	line;
	int		tex_x;
	int		color;
	int		y;
	int		i;

	i = 0;
	y = window.specs.height / 2 - wall.height / 2;
	if (wall.side == 0 || wall.side == 3)
		wall.x = 1 - wall.x;
	tex_x = wall.x * SIZE_TEX;
	step = (double)SIZE_TEX / (double)wall.height;
	line = step;
	color = window.tex[wall.side].addr[tex_x];
	while (i < wall.height)
	{
		if (y >= 0 && y < window.specs.height)
			mlx_pixel_put(window.mlx, window.win, x, y, color);
		line += step;
		if (line < SIZE_TEX)
			color = window.tex[wall.side].addr[tex_x + (int)line * (window.tex[wall.side].size_line / 4)];
		y++;
		i++;
	}
}