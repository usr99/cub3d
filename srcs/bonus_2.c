/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 17:12:26 by mamartin          #+#    #+#             */
/*   Updated: 2021/01/04 20:10:40 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/bonus.h"

void	floor_cast(t_window win)
{
	t_vector	ray0;
	t_vector	ray1;
	t_floor		floor;
	double		row_dist;
	int			y;

	y = 0;
	while (y < win.specs.height)
	{
		ray0.x = win.player.x_dir - win.player.x_plane;
		ray0.y = win.player.y_dir - win.player.y_plane;
		ray1.x = win.player.x_dir + win.player.x_plane;
		ray1.y = win.player.y_dir + win.player.y_plane;
		if (y != win.specs.height / 2)
			row_dist = (double)win.specs.height / (2 * y - win.specs.height);
		floor.step.x = row_dist * (ray1.x - ray0.x) / win.specs.width;
		floor.step.y = row_dist * (ray1.y - ray0.y) / win.specs.width;
		floor.x = win.player.x_pos + row_dist * ray0.x;
		floor.y = win.player.y_pos + row_dist * ray0.y;
		draw_floor(win, floor, y, row_dist);
		y++;
	}
}

void	draw_floor(t_window win, t_floor floor, int y, double dist)
{
	t_vector	cell;
	t_point		tx;
	int			color;
	int			x;

	x = -1;
	while (++x < win.specs.width)
	{
		cell.x = (int)floor.x;
		cell.y = (int)floor.y;
		tx.x = (floor.x - cell.x) * win.tex[5].width;
		tx.y = (floor.y - cell.y) * win.tex[5].height;
		floor.x += floor.step.x;
		floor.y += floor.step.y;
		if (tx.x >= 0 && tx.y >= 0)
		{
			color = win.tex[5].addr[tx.x + tx.y * win.tex[5].width];
			color = shadow(color, dist);
			win.world.addr[x + y * win.specs.width] = color;
			color = win.tex[6].addr[tx.x + tx.y * win.tex[6].width];
			color = shadow(color, dist);
			win.world.addr[x + (win.specs.height - y - 1) * win.specs.width] =
				color;
		}
	}
}

int		shadow(int color, double distance)
{
	int		r;
	int		g;
	int		b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r /= 1 + pow(distance, 2) * 0.05;
	g /= 1 + pow(distance, 2) * 0.05;
	b /= 1 + pow(distance, 2) * 0.05;
	if (r < 0)
		r = 0;
	else if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	else if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	else if (b > 255)
		b = 255;
	color = r << 16 | g << 8 | b;
	return (color);
}
