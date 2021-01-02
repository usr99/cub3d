/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:42:06 by mamartin          #+#    #+#             */
/*   Updated: 2021/01/01 17:30:05 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "cub3d.h"
# include "raycasting.h"

typedef struct	s_data
{
	void			*img;
	unsigned int	*addr;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}				t_data;

typedef struct	s_window
{
	void		*mlx;
	void		*win;
	t_map_specs	specs;
	t_data		tex[5];
	t_data		world;
	t_data		minimap;
	t_player	player;
	double		*depth_walls;
}				t_window;

void			create_window(t_map_specs specs);
void			check_window_size(void *mlx, t_map_specs *specs);
void			create_images(t_window *window, t_map_specs specs);
int				display_window(t_window *window);
void			draw_line(t_window window, int x, t_wall wall);

void			get_player_info(t_window *window, t_map_specs specs);
void			get_player_dir(t_player *player, char c);
void			create_world_image(t_window *win);
void			save_bmp(t_window *w);
void			put_bmp_header(int fd, int image_sz, int ppm, t_map_specs map);

int				handle_event(int keycode, t_window *window);
void			move_camera(t_window *window, int direction, char key);
void			rotate_camera(double *x, double *y, int direction, int rad);

void			free_window(t_window window, int exit_code);
int				exit_cub3d(t_window *win);
void			love_norm(int fd, int *i, int *line, int height);

#endif
