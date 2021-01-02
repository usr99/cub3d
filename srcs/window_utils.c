/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 19:11:29 by mamartin          #+#    #+#             */
/*   Updated: 2021/01/01 18:34:50 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/window.h"
#include "../includes/sprite.h"

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
		player.y_plane = 0.66 * player.x_dir;
	else if (player.y_dir)
		player.x_plane = 0.66 * player.y_dir * -1;
	window->player = player;
}

void	get_player_dir(t_player *player, char c)
{
	player->x_plane = 0;
	player->y_plane = 0;
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

void	create_world_image(t_window *win)
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
	if (win->specs.sprite)
		draw_sprite(*win);
}

void	save_bmp(t_window *w)
{
	int	i;
	int	fd;
	int	line;
	int	pixel;

	fd = open("./save.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	love_norm(fd, &i, &line, w->specs.height);
	put_bmp_header(fd, w->specs.width * w->specs.height * 3, 3779, w->specs);
	create_world_image(w);
	while (line >= 0)
	{
		pixel = i + line * w->specs.width;
		pixel = w->world.addr[pixel];
		write(fd, &pixel, 3);
		i++;
		if (i == w->specs.width)
		{
			if ((w->specs.width * 3) % 4)
				write(fd, "\0\0\0", 4 - (w->specs.width * 3) % 4);
			i = 0;
			line--;
		}
	}
	close(fd);
	free_window(*w, EXIT_SUCCESS);
}

void	put_bmp_header(int fd, int image_sz, int ppm, t_map_specs map)
{
	int	file_sz;

	file_sz = 54 + map.width * map.height * 3;
	file_sz += (4 - (map.width * 3) % 4) * map.height;
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
