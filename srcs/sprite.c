/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 16:00:25 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/27 01:18:56 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sprite.h"

t_vector	*get_sprite_coordinates(char **map)
{
	t_vector	*sprite;
	int			nb_sprites;
	int			i;
	int			j;

	i = 0;
	nb_sprites = 0;
	sprite = NULL;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
			{
				nb_sprites++;
				sprite = get_sprite(sprite, nb_sprites);
				sprite[nb_sprites - 1].x = j + 0.5;
				sprite[nb_sprites - 1].y = i + 0.5;
			}
			j++;
		}
		i++;
	}
	return (sprite);
}

t_vector	*get_sprite(t_vector *sprite, int nb_sprites)
{
	t_vector	*tmp;
	int			i;

	i = 0;
	tmp = sprite;
	sprite = (t_vector *)ft_calloc(nb_sprites + 1, sizeof(t_vector));
	if (!sprite)
		exit(EXIT_FAILURE);
	if (tmp)
	{
		while (i < nb_sprites - 1)
		{
			sprite[i] = tmp[i];
			i++;
		}
		free(tmp);
	}
	sprite[nb_sprites].x = -1;
	sprite[nb_sprites].y = -1;
	return (sprite);
}

void		draw_sprite(t_window window)
{
	int			i;
	int			stripe;
	double		*depth;
	t_sprite	spr;

	i = 0;
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
		if (color != 0x00282828 && y >= 0 && y < window.specs.height)
			window.world.addr[y * window.specs.width + stripe] = color;
		tex_y += (double)window.tex[4].height / (double)spr.size.y;
		if ((int)tex_y >= window.tex[4].height)
			tex_y = window.tex[4].height - 1;
		y++;
	}
}
