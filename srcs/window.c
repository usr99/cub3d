/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 13:02:50 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/23 20:54:56 by mamartin         ###   ########.fr       */
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
	create_world_img(&win, specs);
	create_texture(&win, specs);
	get_player_info(&win, specs);

	display_window(win);
	mlx_do_key_autorepeaton(win.mlx);
	mlx_hook(win.win, 2, 1L << 0, &handle_event, &win);
	mlx_loop(win.mlx);
}

void	create_world_img(t_window *window, t_map_specs specs)
{
	t_img	world;
	int		i;
	int		nb_pixels;


	world.img = mlx_new_image(window->mlx, specs.width, specs.height);
	if (world.img == NULL)
		exit(EXIT_FAILURE);
	nb_pixels = specs.width * specs.height;
	world.addr = (unsigned int *)mlx_get_data_addr(world.img, &world.bpp,
		&world.size_line, &world.endian);
	i = -1;
	while (i++ < nb_pixels / 2)
		world.addr[i] = specs.c_color;
	while (i++ < nb_pixels)
		world.addr[i] = specs.f_color;
	window->world = world;
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
}

void	display_window(t_window window)
{
	t_wall	wall;
	int		x;

	x = 0;
	mlx_put_image_to_window(window.mlx, window.win, window.world.img, 0, 0);
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