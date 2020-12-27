/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 23:05:44 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/27 00:38:35 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define _USE_MATH_DEFINES_

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include "../minilibx/mlx_int.h"

typedef struct	s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct	s_point
{
	int		x;
	int		y;
}				t_point;

typedef struct	s_map_specs
{
	int			width;
	int			height;
	char		*texture[5];
	int			f_color;
	int			c_color;
	char		**map;
	t_vector	*sprite;
	int			save;
}				t_map_specs;

void			init_struct_specs(t_map_specs *specs);
void			is_specs_completed(t_map_specs *specs, char *line);
void			show_error(void *ptr, void (*del)(void *), char *message);
int				check_comma(char *line, int *i);

#endif
