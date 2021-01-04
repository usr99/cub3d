/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 13:02:50 by mamartin          #+#    #+#             */
/*   Updated: 2021/01/04 16:01:28 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/window.h"
#include "../includes/bonus.h"

void	create_window(t_map_specs specs)
{
	t_window	win;

	if (!(win.mlx = mlx_init()))
		exit(EXIT_FAILURE);
	check_window_size(win.mlx, &specs);
	win.specs = specs;
	create_images(&win, specs);
	get_player_info(&win, specs);
	win.world.img = mlx_new_image(win.mlx, specs.width, specs.height);
	win.depth_walls = (double *)malloc(win.specs.width * sizeof(double));
	if (!win.world.img || !win.depth_walls)
		exit(EXIT_FAILURE);
	win.world.addr = (unsigned int *)mlx_get_data_addr(win.world.img,
		&win.world.bpp, &win.world.size_line, &win.world.endian);
	if (specs.save)
		save_bmp(&win);
	win.win = mlx_new_window(win.mlx, specs.width, specs.height, "CUB3D");
	if (!win.win)
		exit(EXIT_FAILURE);
	display_window(&win);
	mlx_do_key_autorepeaton(win.mlx);
	mlx_expose_hook(win.win, &display_window, &win);
	mlx_hook(win.win, 33, 0L, &exit_cub3d, &win);
	mlx_hook(win.win, 2, 1L << 0, &handle_event, &win);
	mlx_loop(win.mlx);
}

void	check_window_size(void *mlx, t_map_specs *specs)
{
	int	screen_width;
	int	screen_height;

	if (!specs->save)
	{
		mlx_get_screen_size(mlx, &screen_width, &screen_height);
		if (specs->width > screen_width)
			specs->width = screen_width;
		if (specs->height > screen_height)
			specs->height = screen_height;
	}
}

void	create_images(t_window *window, t_map_specs specs)
{
	t_data	tx;
	int		i;

	i = 0;
	window->win = NULL;
	tx.width = specs.width / 6;
	tx.height = tx.width;
	tx.img = mlx_new_image(window->mlx, tx.width, tx.height);
	if (tx.img == NULL)
		exit(EXIT_FAILURE);
	tx.addr = (unsigned int *)mlx_get_data_addr(tx.img, &tx.bpp,
		&tx.size_line, &tx.endian);
	window->minimap = tx;
	while (i < 7)
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

int		display_window(t_window *win)
{
	create_world_image(win);
	mlx_put_image_to_window(win->mlx, win->win, win->world.img, 0, 0);
	draw_minimap(win);
	mlx_put_image_to_window(win->mlx, win->win, win->minimap.img, 10, 10);
	mlx_string_put(win->mlx, win->win, win->specs.width / 2 - 20,
		win->specs.height * 0.96, 0x00000000, "100/100");
	return (0);
}

void	draw_line(t_window window, int x, t_wall wall)
{
	double	step;
	double	line;
	int		tex_x;
	int		color;
	int		y;

	y = window.specs.height / 2 - wall.height / 2;
	if (wall.side == 0 || wall.side == 3)
		wall.x = 1 - wall.x;
	tex_x = wall.x * window.tex[wall.side].width;
	step = (double)window.tex[wall.side].height / (double)wall.height;
	line = step;
	color = window.tex[wall.side].addr[tex_x];
	while (wall.height--)
	{
		if (y >= 0 && y < window.specs.height)
			window.world.addr[x + y * (window.world.size_line / 4)] = color;
		line += step;
		if (line < window.tex[wall.side].height)
		{
			color = shadow(window.tex[wall.side].addr[tex_x + (int)line *
				(window.tex[wall.side].size_line / 4)], window.depth_walls[x]);
		}
		y++;
	}
}
