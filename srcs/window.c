/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 13:02:50 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/24 13:46:18 by mamartin         ###   ########.fr       */
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
	if (!(win.world.img = mlx_new_image(win.mlx, specs.width, specs.height)))
		exit(EXIT_FAILURE);

	win.world.addr = (unsigned int *)mlx_get_data_addr(win.world.img,
		&win.world.bpp, &win.world.size_line, &win.world.endian);
	win.specs = specs;
	create_texture(&win, specs);
	get_player_info(&win, specs);

	display_window(&win);
	if (specs.save)
		save_bmp(win.world, specs);
	mlx_do_key_autorepeaton(win.mlx);

	//mlx_hook(win.win, 33, 0, &close_cub3d, &win);
	
	mlx_expose_hook(win.win, &display_window, &win);
	mlx_hook(win.win, 2, 1L << 0, &handle_event, &win);
	mlx_loop(win.mlx);
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

int		display_window(t_window *window)
{
	t_wall	wall;
	int		x;
	int		i;
	int		nb_pixels;

	i = -1;
	nb_pixels = window->specs.width * window->specs.height;
	while (i++ < nb_pixels / 2)
		window->world.addr[i] = window->specs.c_color;
	while (i++ < nb_pixels)
		window->world.addr[i] = window->specs.f_color;
	x = 0;
	while (x < window->specs.width)
	{
		wall = raycast(window->player, window->specs, x);
		draw_line(*window, x, wall);
		x++;
	}
	mlx_put_image_to_window(window->mlx, window->win, window->world.img, 0, 0);
	return (0);
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
			window.world.addr[x + y * (window.world.size_line / 4)] = color;
		line += step;
		if (line < SIZE_TEX)
			color = window.tex[wall.side].addr[tex_x + (int)line * (window.tex[wall.side].size_line / 4)];
		y++;
		i++;
	}
}

void	save_bmp(t_img world, t_map_specs specs)
{
	int	fd;
	int	file_size;
	int	image_size;
	int	pixel_per_meter;
	int	i;
	int	line;
	int	pixel;

	fd = open("./save.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
		exit(EXIT_FAILURE);
	file_size = 54 + specs.width * specs.height * 3;
	file_size += file_size % 4;
	// file header
	write(fd, "BM", 2);
	write(fd, &file_size, 4);
	write(fd, "\0\0\0\0", 4);
	ft_putchar_fd(54, fd);
	write(fd, "\0\0\0", 3);
	// image header
	ft_putchar_fd(40, fd);
	write(fd, "\0\0\0", 3);
	write(fd, &specs.width, 4);
	write(fd, &specs.height, 4);
	ft_putchar_fd(1, fd);
	ft_putchar_fd(0, fd);
	ft_putchar_fd(24, fd);
	write(fd, "\0\0\0\0\0", 5);
	image_size = specs.width * specs.height * 3;
	write(fd, &image_size, 4);
	pixel_per_meter = 3779;
	write(fd, &pixel_per_meter, 4);
	write(fd, &pixel_per_meter, 4);
	write(fd, "\0\0\0\0\0\0\0\0", 8);
	// image data
	i = 0;
	line = specs.height - 2;
	while (line >= 0)
	{
		pixel = i + line * world.size_line / 4;
		ft_putchar_fd(world.addr[pixel], fd);
		ft_putchar_fd(world.addr[pixel] >> 8, fd);
		ft_putchar_fd(world.addr[pixel] >> 16, fd);
		i++;
		if (i == specs.width)
		{
			i = 0;
			line--;
		}
	}
	write(fd, "\0\0\0", (image_size + 54) % 4);
	close(fd);
}
