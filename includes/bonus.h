/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 16:35:59 by mamartin          #+#    #+#             */
/*   Updated: 2021/01/02 23:46:36 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "window.h"

typedef struct	s_floor
{
	double		x;
	double		y;
	t_vector	step;
}				t_floor;

int				check_collision(char tile, double x, double y);
void			draw_minimap(t_window *window);
void			get_map_size(char **map, double *big_lines, double *nb_lines);
void			set_minimap_color(t_window win, t_vector pos, int x, int y);
void			draw_life_bar(t_window win);

void			floor_cast(t_window win);
void			draw_floor(t_window win, t_floor floor, int y);

#endif
