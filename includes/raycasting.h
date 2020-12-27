/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:43:22 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/27 00:36:50 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

typedef struct	s_player
{
	double	x_pos;
	double	y_pos;
	double	x_dir;
	double	y_dir;
	double	x_plane;
	double	y_plane;
}				t_player;

typedef struct	s_wall
{
	int		side;
	int		height;
	double	x;
	double	dist;
}				t_wall;

typedef struct	s_ray
{
	t_vector	dir;
	t_vector	delta;
	t_vector	side;
	t_point		map;
	t_point		step;
}				t_ray;

t_wall			raycast(t_player player, t_map_specs specs, int x);
void			get_ray_data(t_player player, t_ray *ray);
void			get_ray_step(t_player player, t_ray *ray);
void			find_wall(t_player pl, t_map_specs specs, t_ray ray,
					t_wall *wall);
void			get_wall_data(t_player player, t_ray ray, t_wall *wall);

#endif
