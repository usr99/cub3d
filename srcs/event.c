/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 16:04:51 by mamartin          #+#    #+#             */
/*   Updated: 2021/01/02 01:33:47 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/window.h"
#include "../includes/bonus.h"

int		handle_event(int keycode, t_window *window)
{
	if (keycode == 'w')
		move_camera(window, 1, 'w');
	else if (keycode == 's')
		move_camera(window, -1, 's');
	else if (keycode == 'a')
		move_camera(window, -1, 'a');
	else if (keycode == 'd')
		move_camera(window, 1, 'd');
	else if (keycode == XK_Left)
	{
		rotate_camera(&window->player.x_dir, &window->player.y_dir, -1, 25);
		rotate_camera(&window->player.x_plane, &window->player.y_plane, -1, 25);
	}
	else if (keycode == XK_Right)
	{
		rotate_camera(&window->player.x_dir, &window->player.y_dir, 1, 25);
		rotate_camera(&window->player.x_plane, &window->player.y_plane, 1, 25);
	}
	else if (keycode == XK_Escape)
		free_window(*window, EXIT_SUCCESS);
	display_window(window);
	return (0);
}

void	move_camera(t_window *window, int direction, char key)
{
	double x;
	double y;
	double dir_x;
	double dir_y;

	x = window->player.x_pos;
	y = window->player.y_pos;
	dir_x = window->player.x_dir;
	dir_y = window->player.y_dir;
	if (key == 'a' || key == 'd')
		rotate_camera(&dir_x, &dir_y, direction, 2);
	if (key == 'a')
		direction = 1;
	x += dir_x * 0.20 * direction;
	y += dir_y * 0.20 * direction;
	if (check_collision(window->specs.map[(int)y][(int)x], x, y))
	{
		x += dir_x * 0.01 * direction;
		y += dir_y * 0.01 * direction;
		if (check_collision(window->specs.map[(int)y][(int)x], x, y))
		{
			window->player.x_pos = x - dir_x * 0.01 * direction;
			window->player.y_pos = y - dir_y * 0.01 * direction;
		}
	}
}

void	rotate_camera(double *x, double *y, int direction, int rad)
{
	double tmp;
	double rot;

	tmp = *x;
	rot = (M_PI * direction) / rad;
	*x = *x * cos(rot) - *y * sin(rot);
	*y = tmp * sin(rot) + *y * cos(rot);
}
