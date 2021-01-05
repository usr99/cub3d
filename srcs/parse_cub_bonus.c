/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:19:31 by mamartin          #+#    #+#             */
/*   Updated: 2021/01/04 21:04:23 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../includes/sprite.h"

void	parse_map(int fd, t_map_specs *specs)
{
	char	*line;
	int		ret;

	while ((ret = get_next_line(fd, &line)))
	{
		if (ret == -1)
			show_error(NULL, NULL, "Can't read file");
		ret = -1;
		if (ft_strchr("NSWEFC", line[0]))
			ret = get_texture(line, specs);
		else if (line[0] == 'R')
			ret = get_res(line, specs);
		else if (is_map_description(line))
			break ;
		if (ret == -1 && ft_strlen(line) > 0)
			show_error(line, &free, "Invalid .cub file");
		free(line);
	}
	if (ret == 0)
		show_error(NULL, NULL, "Map description missing/incorrect");
	is_specs_completed(specs, line);
	specs->map = get_map(line, fd);
	specs->sprite = get_sprite_coordinates(specs->map);
}

int		get_texture(char *line, t_map_specs *m_specs)
{
	char	*texture;
	int		i;

	i = 2;
	if (ft_strchr("SFC", line[0]) && line[1] != 'O')
		i = 1;
	while (line[i] == ' ')
		i++;
	texture = ft_strdup(line + i);
	if (!texture)
	{
		free(line);
		free_specs(m_specs);
		exit(EXIT_FAILURE);
	}
	return (set_spec(line, m_specs, texture));
}

int		set_spec(char *line, t_map_specs *m_specs, void *value)
{
	if (ft_strnstr(line, "NO ", 3) && !m_specs->texture[0])
		m_specs->texture[0] = (char *)value;
	else if (ft_strnstr(line, "SO ", 3) && !m_specs->texture[1])
		m_specs->texture[1] = (char *)value;
	else if (ft_strnstr(line, "WE ", 3) && !m_specs->texture[2])
		m_specs->texture[2] = (char *)value;
	else if (ft_strnstr(line, "EA ", 3) && !m_specs->texture[3])
		m_specs->texture[3] = (char *)value;
	else if (ft_strnstr(line, "S ", 2) && !m_specs->texture[4])
		m_specs->texture[4] = (char *)value;
	else if (ft_strnstr(line, "F ", 2) && !m_specs->texture[5])
		m_specs->texture[5] = (char *)value;
	else if (ft_strnstr(line, "C ", 2) && !m_specs->texture[6])
		m_specs->texture[6] = (char *)value;
	else
	{
		free(value);
		return (-1);
	}
	return (0);
}

int		get_res(char *line, t_map_specs *m_specs)
{
	int i;

	i = 1;
	if (m_specs->width || m_specs->height)
		show_error(line, &free, "Resolution is set twice");
	while (line[i] == ' ')
		i++;
	if (i == 1)
		show_error(line, &free, "Bad value for resolution");
	m_specs->width = ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	m_specs->height = ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		i++;
	if (m_specs->width < 1 || m_specs->height < 1 || line[i] != '\0')
		show_error(line, &free, "Bad value for resolution");
	return (0);
}
