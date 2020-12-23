/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:42:06 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/23 19:59:43 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# define SIZE_TEX 256

# include "cub3d.h"
# include "raycasting.h"

typedef struct	s_img
{
	void			*img;
	unsigned int	*addr;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}				t_img;

typedef struct	s_window
{
	void		*mlx;
	void		*win;
	t_map_specs	specs;
	t_img		floor;
	t_img		sky;
	t_img		tex[5];
	t_img		walls;
	t_player	player;

}				t_window;

void			create_window(t_map_specs specs);
void			create_floor_and_sky(t_window *window, t_map_specs specs);
void			create_texture(t_window *window, t_map_specs specs);
void			display_window(t_window window);
void			draw_line(t_window window, int x, t_wall wall);

void			get_player_info(t_window *window, t_map_specs specs);
void			get_player_dir(t_player *player, char c);
int				handle_event(int keycode, t_window *window);
void			check_wall(t_window *window, int direction);

#endif