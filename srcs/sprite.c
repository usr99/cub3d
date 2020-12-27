/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 16:00:25 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/27 20:18:24 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sprite.h"

void		draw_sprite(t_window window)
{
	int			i;
	int			stripe;
	double		*depth;
	t_sprite	spr;

	i = 0;
	sort_sprites(window.player, window.specs.sprite);
	depth = window.depth_walls;
	while (window.specs.sprite[i].x != -1)
	{
		spr = get_sprite_data(window.player, window.specs.sprite[i],
			window.specs);
		stripe = spr.draw_start.x;
		while (stripe <= spr.draw_end.x)
		{
			if (stripe >= 0 && stripe < window.specs.width)
			{
				if (spr.transform.y > 0 && spr.transform.y < depth[stripe])
				{
					draw_stripe(window, spr, stripe);
				}
			}
			stripe++;
		}
		i++;
	}
}

void		sort_sprites(t_player player, t_vector *sprite)
{
	t_vector	tmp;
	double		dist1;
	double		dist2;
	int			i;
	int			j;

	i = 0;
	while (sprite[i].x != -1)
	{
		j = 0;
		while (sprite[j + 1].x != -1)
		{
			dist1 = pow(player.x_pos - sprite[j].x, 2);
			dist1 += pow(player.y_pos - sprite[j].y, 2);
			dist2 = pow(player.x_pos - sprite[j + 1].x, 2);
			dist2 += pow(player.y_pos - sprite[j + 1].y, 2);
			if (dist1 < dist2)
			{
				tmp = sprite[j];
				sprite[j] = sprite[j + 1];
				sprite[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

t_sprite	get_sprite_data(t_player pl, t_vector pos, t_map_specs specs)
{
	t_sprite	spr;
	double		inv_cam_matrix;

	spr.dist.x = pos.x - pl.x_pos;
	spr.dist.y = pos.y - pl.y_pos;
	inv_cam_matrix = (1.0 / (pl.x_plane * pl.y_dir - pl.x_dir * pl.y_plane));
	spr.transform.x = inv_cam_matrix * (pl.y_dir * spr.dist.x - pl.x_dir
		* spr.dist.y);
	spr.transform.y = inv_cam_matrix * (-pl.y_plane * spr.dist.x + pl.x_plane
		* spr.dist.y);
	spr.screen_x = (int)((specs.width / 2) * (1 + spr.transform.x
		/ spr.transform.y));
	spr.size.y = abs((int)(specs.height / spr.transform.y));
	spr.draw_start.y = -spr.size.y / 2 + specs.height / 2;
	spr.draw_end.y = spr.size.y / 2 + specs.height / 2;
	spr.size.x = spr.size.y;
	spr.draw_start.x = -spr.size.x / 2 + spr.screen_x;
	if (spr.draw_start.x < 0)
		spr.draw_start.x = 0;
	spr.draw_end.x = spr.size.x / 2 + spr.screen_x;
	if (spr.draw_end.x > specs.width)
		spr.draw_end.x = specs.width - 1;
	return (spr);
}

void		draw_stripe(t_window window, t_sprite spr, int stripe)
{
	double	tex_y;
	int		tex_x;
	int		color;
	int		y;

	y = spr.draw_start.y;
	tex_x = (int)((stripe - (-spr.size.x / 2 + spr.screen_x))
		* window.tex[4].width / spr.size.x);
	tex_y = (double)window.tex[4].height / (double)spr.size.y;
	while (y < spr.draw_end.y)
	{
		color = window.tex[4].addr[(int)tex_y * window.tex[4].width + tex_x];
		if (color != 0x00FF00FF && y >= 0 && y < window.specs.height)
			window.world.addr[y * window.specs.width + stripe] = color;
		tex_y += (double)window.tex[4].height / (double)spr.size.y;
		if ((int)tex_y >= window.tex[4].height)
			tex_y = window.tex[4].height - 1;
		y++;
	}
}
