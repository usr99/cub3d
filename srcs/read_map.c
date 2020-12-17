/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:11:02 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/17 18:09:20 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		is_map_description(char *line)
{
	int i;
	int	is_wall;

	i = 0;
	is_wall = 0;
	if (!line || ft_strlen(line) == 0)
		return (0);
	while (line[i] == '1' || line[i] == ' ')
	{
		if (line[i] == '1')
			is_wall = 1;
		i++;
	}
	if (line[i] != '\0' || !is_wall)
		return (0);
	return (1);
}

char	**get_map(char *line, int fd)
{
	char	**map;
	char	**tmp;
	int		nb_lines;
	int		i;

	nb_lines = 0;
	map = NULL;
	while (ft_strlen(line) != 0)
	{
		nb_lines++;
		tmp = map;
		map = (char **)ft_calloc(nb_lines + 1, sizeof(char *));
		if (!map)
			exit(EXIT_FAILURE);
		i = -1;
		while (++i < nb_lines - 1)
			map[i] = tmp[i];
		if (tmp)
			free(tmp);
		map[i] = line;
		get_next_line(fd, &line);
	}
	free(line);
	check_map(map);
	return (map);
}

void	check_map(char **map)
{
	int	i;
	int	j;
	int	x_player;
	int	y_player;

	i = 0;
	j = 0;
	x_player = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (ft_strchr("NSWE", map[i][j]))
			{
				if (x_player)
					show_error(NULL, PLAYER_TWICE);
				x_player = j;
				y_player = i;
			}
			else if (!ft_strchr(" 012", map[i][j]))
				show_error(NULL, BAD_MAP);
			j++;
		}
		i++;
	}
	pathfinding(map, y_player, x_player);
}

void	pathfinding(char **map, int i, int j)
{
	if (map[i][j] == '1')
		return ;
	if (map[i][j] == ' ' || map[i][j] == '\0')
	{
		ft_free_map(map);
		show_error(NULL, MAP_NOT_CLOSED);
	}
	if (i != 0 && j < ft_strlen(map[i - 1]))
		pathfinding(map, i - 1, j);
	if (map[i + 1] != NULL && j < ft_strlen(map[i + 1]))
		pathfinding(map, i + 1, j);
	if (j > 0)
		pathfinding(map, i, j - 1);
	pathfinding(map, i, j + 1);
}
