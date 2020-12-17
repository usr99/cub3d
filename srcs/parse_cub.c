/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 20:19:31 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/16 18:51:07 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parse_map(int fd, t_map_specs *specs)
{
	char	*line;
	int		ret;

	while ((ret = get_next_line(fd, &line)))
	{
		if (ret == -1)
			show_error(NULL, READ_FILE);
		ret = -1;
		if (ft_strchr("NSWE", line[0]))
			ret = get_texture(line, specs);
		else if (ft_strchr("FC", line[0]))
			ret = get_color(line, specs);
		else if (line[0] == 'R')
			ret = get_res(line, specs);
		else if (is_map_description(line))
			break ;
		if (ret == -1 && ft_strlen(line) > 0)
			show_error(line, INVALID_FILE);
		free(line);
	}
	if (ret == 0)
		show_error(NULL, MISSING_MAP);
	is_specs_completed(specs, line);
	specs->map = get_map(line, fd);
}

int		get_texture(char *line, t_map_specs *m_specs)
{
	char	*texture;
	int		i;

	i = 2;
	if (line[0] == 'S' && line[1] != 'O')
		i = 1;
	while (line[i] == ' ')
		i++;
	texture = ft_strdup(line + i);
	if (!texture)
	{
		free(line);
		free(texture);
		exit(EXIT_FAILURE);
	}
	return (set_spec(line, m_specs, texture));
}

int		get_color(char *line, t_map_specs *m_specs)
{
	int i;
	int color;
	int bit_shift;
	int byte;

	i = 1;
	color = 0;
	bit_shift = 16;
	while (line[i] && bit_shift != -8)
	{
		while (line[i] == ' ')
			i++;
		if (!ft_isdigit(line[i]))
			show_error(line, BAD_RGB_VALUE);
		byte = ft_atoi(line + i);
		if (byte < 0 || byte > 255)
			show_error(line, BAD_RGB_VALUE);
		color = (color | byte << bit_shift);
		bit_shift -= 8;
		if (check_comma(line, &i) == -1 && bit_shift != -8)
			show_error(line, BAD_RGB_VALUE);
	}
	if (line[i] != '\0' || (line[i] == '\0' && bit_shift != -8))
		show_error(line, BAD_RGB_VALUE);
	return (set_spec(line, m_specs, &color));
}

int		set_spec(char *line, t_map_specs *m_specs, void *value)
{
	if (ft_strnstr(line, "NO ", 3) && !m_specs->no_texture)
		m_specs->no_texture = (char *)value;
	else if (ft_strnstr(line, "SO ", 3) && !m_specs->so_texture)
		m_specs->so_texture = (char *)value;
	else if (ft_strnstr(line, "WE ", 3) && !m_specs->we_texture)
		m_specs->we_texture = (char *)value;
	else if (ft_strnstr(line, "EA ", 3) && !m_specs->ea_texture)
		m_specs->ea_texture = (char *)value;
	else if (ft_strnstr(line, "S ", 2) && !m_specs->s_texture)
		m_specs->s_texture = (char *)value;
	else if (ft_strnstr(line, "F ", 2) && !m_specs->f_color)
		m_specs->f_color = *((int*)value);
	else if (ft_strnstr(line, "C ", 2) && !m_specs->c_color)
		m_specs->c_color = *((int*)value);
	else
	{
		if (!ft_strchr("FC", line[0]))
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
		show_error(line, ALREADY_RES);
	while (line[i] == ' ')
		i++;
	if (i == 1)
		show_error(line, BAD_RES_VALUE);
	m_specs->width = ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		i++;
	while (line[i] == ' ')
		i++;
	m_specs->height = ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		i++;
	if (m_specs->width < 1 || m_specs->height < 1 || line[i] != '\0')
		show_error(line, BAD_RES_VALUE);
	return (0);
}
