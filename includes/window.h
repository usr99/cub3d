/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:42:06 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/19 18:56:08 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "cub3d.h"

typedef struct	s_data_img
{
	void			*img;
	unsigned int	*addr;
	int				bpp;
	int				size_line;
	int				endian;
}				t_data_img;

void	create_window(t_map_specs specs);
void	display_floor_and_sky(void *mlx, void *win, t_map_specs specs);
void	raycast(void *mlx, void *win, t_map_specs specs);

#endif