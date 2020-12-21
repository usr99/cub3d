/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 19:11:29 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/22 00:21:20 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysym.h>
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

int	handle_event(int keycode, t_window *window)
{
	double	tmp_dirX = window->player.dirX;
	double	tmp_planeX = window->player.planeX;

	if (keycode == XK_Up)
	{
		window->player.posX += window->player.dirX * 0.25;
		window->player.posY += window->player.dirY * 0.25;
	}
	else if (keycode == XK_Down)
	{
		window->player.posX -= window->player.dirX * 0.25;
		window->player.posY -= window->player.dirY * 0.25;
	}
	else if (keycode == XK_Left)
	{
		window->player.dirX = window->player.dirX * cos(-M_PI / 16) - window->player.dirY * sin(-M_PI / 16);
		window->player.dirY = tmp_dirX * sin(-M_PI / 16) + window->player.dirY * cos(-M_PI / 16);
		window->player.planeX = window->player.planeX * cos(-M_PI / 16) - window->player.planeY * sin(-M_PI / 16);
		window->player.planeY = tmp_planeX * sin(-M_PI / 16) + window->player.planeY * cos(-M_PI / 16);
	}
	else if (keycode == XK_Right)
	{
		window->player.dirX = window->player.dirX * cos(M_PI / 16) - window->player.dirY * sin(M_PI / 16);
		window->player.dirY = tmp_dirX * sin(M_PI / 16) + window->player.dirY * cos(M_PI / 16);
		window->player.planeX = window->player.planeX * cos(M_PI / 16) - window->player.planeY * sin(M_PI / 16);
		window->player.planeY = tmp_planeX * sin(M_PI / 16) + window->player.planeY * cos(M_PI / 16);
	}
	display_window(*window);
	return (0);
}