/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 16:38:49 by mamartin          #+#    #+#             */
/*   Updated: 2021/01/02 02:20:41 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

int		check_collision(char tile, double x, double y)
{
	t_vector	sprite_pos;
	double		dist;

	if (tile == '1')
		return (0);
	else if (tile == '2')
	{
		sprite_pos.x = (int)x + 0.5;
		sprite_pos.y = (int)y + 0.5;
		dist = sqrt(pow(sprite_pos.x - x, 2) + pow(sprite_pos.y - y, 2));
		if (dist < 0.2)
			return (0);
	}
	return (1);
}

void	draw_minimap(t_window *window)
{
	t_vector	step;
	t_vector	pos;
	int			x;
	int			y;

	x = 0;
	y = 0;
	pos.x = 0;
	pos.y = 0;
	get_map_size(window->specs.map, &step.x, &step.y);
	step.x = step.x / window->minimap.width;
	step.y = step.y / window->minimap.height;
	while (y != window->minimap.height)
	{
		set_minimap_color(*window, pos, x, y);
		pos.x += step.x;
		x++;
		if (x == window->minimap.width)
		{
			x = 0;
			y++;
			pos.x = 0;
			pos.y += step.y;
		}
	}
}

void	get_map_size(char **map, double *big_lines, double *nb_lines)
{
	int		i;
	int		size_line;

	i = 0;
	*big_lines = 0;
	while (map[i])
	{
		size_line = (int)ft_strlen(map[i]);
		if (size_line > *big_lines)
			*big_lines = size_line;
		i++;
	}
	*nb_lines = i;
}

void	set_minimap_color(t_window win, t_vector pos, int x, int y)
{
	t_point		player;

	player.x = (int)win.player.x_pos;
	player.y = (int)win.player.y_pos;
	if (!x || !y || x == win.minimap.width - 1 || y == win.minimap.height - 1)
		win.minimap.addr[x + y * win.minimap.width] = 0x00C79A20;
	else if (player.x == (int)pos.x && player.y == (int)pos.y)
		win.minimap.addr[x + y * win.minimap.width] = 0x00C79A20;
	else if (win.specs.map[(int)pos.y] && pos.x < ft_strlen(win.specs.map[(int)pos.y]))
	{
		if (win.specs.map[(int)pos.y][(int)pos.x] == '1')
			win.minimap.addr[x + y * win.minimap.width] = 0x00303030;
		else
			win.minimap.addr[x + y * win.minimap.width] = 0x00505050;
	}
	else
		win.minimap.addr[x + y * win.minimap.width] = 0x00505050;
}
