/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 19:11:29 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/26 19:31:48 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/window.h"

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
				player.x_pos = (double)j + 0.5;
				player.y_pos = (double)i + 0.5;
			}
			j++;
		}
		i++;
	}
	if (player.x_dir)
		player.y_plane = 0.66;
	else if (player.y_dir)
		player.x_plane = 0.66;
	window->player = player;
}

void	get_player_dir(t_player *player, char c)
{
	player->x_dir = 0;
	player->y_dir = 0;
	if (c == 'N')
		player->y_dir = -1.0;
	else if (c == 'S')
		player->y_dir = 1.0;
	else if (c == 'W')
		player->x_dir = -1.0;
	else if (c == 'E')
		player->x_dir = 1.0;
}

void	save_bmp(t_data world, t_map_specs specs)
{
	int	i;
	int	fd;
	int	line;
	int	pixel;

	fd = open("./save.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd == -1)
		exit(EXIT_FAILURE);
	put_bmp_header(fd, specs.width * specs.height * 3, 3779, specs);
	i = 0;
	line = specs.height - 1;
	while (line >= 0)
	{
		pixel = i + line * world.size_line / 4;
		pixel = world.addr[pixel];
		write(fd, &pixel, 3);
		i++;
		if (i == specs.width)
		{
			i = 0;
			line--;
		}
	}
	write(fd, "\0\0\0", (specs.width * specs.height * 3 + 54) % 4);
	close(fd);
}

void	put_bmp_header(int fd, int image_sz, int ppm, t_map_specs map)
{
	int	file_sz;

	file_sz = 54 + map.width * map.height * 3;
	file_sz += file_sz % 4;
	write(fd, "BM", 2);
	write(fd, &file_sz, 4);
	write(fd, "\0\0\0\0", 4);
	ft_putchar_fd(54, fd);
	write(fd, "\0\0\0", 3);
	ft_putchar_fd(40, fd);
	write(fd, "\0\0\0", 3);
	write(fd, &map.width, 4);
	write(fd, &map.height, 4);
	ft_putchar_fd(1, fd);
	ft_putchar_fd(0, fd);
	ft_putchar_fd(24, fd);
	write(fd, "\0\0\0\0\0", 5);
	write(fd, &image_sz, 4);
	write(fd, &ppm, 4);
	write(fd, &ppm, 4);
	write(fd, "\0\0\0\0\0\0\0\0", 8);
}

void	free_window(t_window window, int exit_code)
{
	int	i;

	i = 4;
	while (i--)
	{
		free(window.specs.texture[i]);
		mlx_destroy_image(window.mlx, window.tex[i].img);
	}
	ft_free_map(window.specs.map);
	ft_free_map(window.specs.sprite);
	free(window.depth_walls);
	mlx_destroy_image(window.mlx, window.world.img);
	mlx_destroy_window(window.mlx, window.win);
	mlx_destroy_display(window.mlx);
	exit(exit_code);
}
