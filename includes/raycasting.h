/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:43:22 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/22 00:20:39 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

typedef struct  s_player
{
    double	posX;
    double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
}               t_player;

int 	        raycast(t_player player, t_map_specs specs, int x, int *color);

#endif