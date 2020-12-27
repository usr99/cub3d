/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 23:36:06 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/27 18:33:49 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include "cub3d.h"
# include "window.h"

typedef struct	s_sprite
{
	t_vector	dist;
	t_vector	transform;
	t_point		draw_start;
	t_point		draw_end;
	t_point		size;
	int			screen_x;
}				t_sprite;

void			draw_sprite(t_window window);
void			sort_sprites(t_player player, t_vector *sprite);
t_sprite		get_sprite_data(t_player pl, t_vector pos, t_map_specs specs);
void			draw_stripe(t_window window, t_sprite spr, int stripe);

t_vector		*get_sprite_coordinates(char **map);
t_vector		*get_sprite(t_vector *sprite, int nb_sprites);

#endif
