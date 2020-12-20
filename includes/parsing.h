/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 17:33:30 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/18 17:43:22 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

void    parse_map(int fd, t_map_specs *specs);
int     get_texture(char *line, t_map_specs *m_specs);
int     get_color(char *line, t_map_specs *m_specs);
int     set_spec(char *line, t_map_specs *m_specs, void *value);
int     get_res(char *line, t_map_specs *m_specs);

int     is_map_description(char *line);
char    **get_map(char *line, int fd);
void    check_map(char **map);
void    check_map_closed(char **map, int x, int y);
void    pathfinding(char **map, int i, int j);

#endif