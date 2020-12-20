/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 13:02:50 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/20 19:25:36 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/window.h"

void	create_window(t_map_specs specs)
{
	t_window	win;

	win.specs = specs;
	if (!(win.mlx = mlx_init()))
		exit(EXIT_FAILURE);
	win.win = mlx_new_window(win.mlx, specs.width, specs.height, "CUB3D");
	if (win.win == NULL)
		exit(EXIT_FAILURE);
	create_floor_and_sky(&win, specs);
	get_player_info(&win, specs);
	display_window(win);
	mlx_key_hook(win.win, &handle_event, &win);
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

void	get_player_info(t_window *window, t_map_specs specs)
{
	t_player	player;
	int			i;
	int			j;

	i = 0;
	while (specs.map[i])
	{
		j = 0;
		while (specs.map[i][j])
		{
			if (ft_strchr("NSWE", specs.map[i][j]))
			{
				get_player_dir(&player, specs.map[i][j]);
				player.posX = (double)j + 0.5;
				player.posY = (double)i + 0.5;
			}
			j++;
		}
		i++;
	}
	if (player.dirX)
		player.planeY = 0.66;
	else if (player.dirY)
		player.planeX = 0.66;
	window->player = player;
}

void	get_player_dir(t_player *player, char c)
{
	player->dirX = 0;
	player->dirY = 0;
	if (c == 'N')
		player->dirY = -1.0;
	else if (c == 'S')
		player->dirY = 1.0;
	else if (c == 'W')
		player->dirX = -1.0;
	else if (c == 'E')
		player->dirX = 1.0;
}

void	display_window(t_window window)
{
	int	color;
	int	line_height;
	int	bottom;
	int	top;
	int	x;

	x = 0;
	mlx_put_image_to_window(window.mlx, window.win, window.floor.img, 0,
		window.specs.height / 2);
	mlx_put_image_to_window(window.mlx, window.win, window.sky.img, 0, 0);
	while (x < window.specs.width)
	{
		line_height = raycast(window.player, window.specs, x, &color);
		
		bottom = -line_height / 2 + window.specs.height / 2;
		if (bottom < 0)
			bottom = 0;
		top = line_height / 2 + window.specs.height / 2;
		if (top > window.specs.height)
			top = window.specs.height;

		for (int y = bottom ; y < top ; y++)
			mlx_pixel_put(window.mlx, window.win, x, y, color);

		x++;
	}
}
