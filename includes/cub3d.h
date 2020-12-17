/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 23:05:44 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/17 18:06:51 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"

typedef enum    e_error
{
    TOO_FEW_ARG, READ_FILE, INVALID_FILE, MISSING_MAP, MISSING_VALUE,
    BAD_RGB_VALUE, ALREADY_RES, BAD_RES_VALUE, BAD_MAP, PLAYER_TWICE,
    MAP_NOT_CLOSED
}               t_error;

typedef struct  s_map_specs
{
    int     width;
    int     height;
    char    *no_texture;
    char    *so_texture;
    char    *we_texture;
    char    *ea_texture;
    char    *s_texture;
    int     f_color;
    int     c_color;
    char    **map;
}               t_map_specs;

void			init_struct_specs(t_map_specs *specs);
void	        is_specs_completed(t_map_specs *specs, char *line);
void        	show_error(void *ptr, t_error id_error);
int		        check_comma(char *line, int *i);

void			parse_map(int fd, t_map_specs *specs);
int         	get_texture(char *line, t_map_specs *m_specs);
int         	get_color(char *line, t_map_specs *m_specs);
int         	set_spec(char *line, t_map_specs *m_specs, void *value);
int         	get_res(char *line, t_map_specs *m_specs);

int         	is_map_description(char *line);
char        	**get_map(char *line, int fd);
void	        check_map(char **map);
void	        pathfinding(char **map, int i, int j);

#endif