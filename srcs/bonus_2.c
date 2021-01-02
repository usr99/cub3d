/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 17:12:26 by mamartin          #+#    #+#             */
/*   Updated: 2021/01/02 23:47:43 by mamartin         ###   ########.fr       */
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
		draw_floor(win, floor, y);
		y++;
	}
}

void	draw_floor(t_window win, t_floor floor, int y)
{
	t_vector	cell;
	t_point		tx;
	int			color;
	int			x;

	x = 0;
	while (x < win.specs.width)
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
			win.world.addr[x + y * win.specs.width] = color;
			color = win.tex[6].addr[tx.x + tx.y * win.tex[6].width];
			win.world.addr[x + (win.specs.height - y - 1) * win.specs.width] =
				color;
		}
		x++;
	}
}
