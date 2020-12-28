/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 13:02:50 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/27 22:35:11 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/window.h"
#include "../includes/sprite.h"

void	create_window(t_map_specs specs)
{
	t_window	win;

	if (!(win.mlx = mlx_init()))
		exit(EXIT_FAILURE);
	check_window_size(win.mlx, &specs);
	win.win = mlx_new_window(win.mlx, specs.width, specs.height, "CUB3D");
	win.world.img = mlx_new_image(win.mlx, specs.width, specs.height);
	win.specs = specs;
	win.depth_walls = (double *)malloc(win.specs.width * sizeof(double));
	if (!win.win || !win.world.img || !win.depth_walls)
		exit(EXIT_FAILURE);
	win.world.addr = (unsigned int *)mlx_get_data_addr(win.world.img,
		&win.world.bpp, &win.world.size_line, &win.world.endian);
	create_texture(&win, specs);
	get_player_info(&win, specs);
	display_window(&win);
	if (specs.save)
		save_bmp(win.world, specs);
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

	mlx_get_screen_size(mlx, &screen_width, &screen_height);
	if (specs->width > screen_width)
		specs->width = screen_width;
	if (specs->height > screen_height)
		specs->height = screen_height;
}

void	create_texture(t_window *window, t_map_specs specs)
{
	t_data	tx;
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

int		display_window(t_window *win)
{
	t_wall	wall;
	int		x;
	int		i;
	int		nb_pixels;

	i = -1;
	nb_pixels = win->specs.width * win->specs.height;
	while (i++ < nb_pixels / 2)
		win->world.addr[i] = win->specs.c_color;
	while (i++ < nb_pixels)
		win->world.addr[i] = win->specs.f_color;
	x = 0;
	while (x < win->specs.width)
	{
		wall = raycast(win->player, win->specs, x);
		win->depth_walls[x] = wall.dist;
		draw_line(*win, x, wall);
		x++;
	}
	draw_sprite(*win);
	mlx_put_image_to_window(win->mlx, win->win, win->world.img, 0, 0);
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
			color = window.tex[wall.side].addr[tex_x + (int)line
				* (window.tex[wall.side].size_line / 4)];
		}
		y++;
	}
}
