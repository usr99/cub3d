/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:11:02 by mamartin          #+#    #+#             */
/*   Updated: 2021/01/06 14:35:29 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int		is_map_description(char *line)
{
	int i;

	i = 0;
	if (!line || ft_strlen(line) == 0)
		return (0);
	while (ft_strchr(" 012", line[i]))
		i++;
	if (line[i] != '\0')
		return (0);
	return (1);
}

char	**get_map(char *line, int fd, t_map_specs *specs)
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
	check_map(map, specs);
	return (map);
}

void	check_map(char **map, t_map_specs *specs)
{
	int	i;
	int	j;
	int	x_player;
	int	y_player;

	i = -1;
	x_player = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSWE", map[i][j]))
			{
				if (x_player != -1)
					show_error(map, &ft_free_map, "Player set twice", specs);
				x_player = j;
				y_player = i;
			}
			else if (!ft_strchr(" 012", map[i][j]))
				show_error(map, &ft_free_map, "Bad character in map", specs);
			j++;
		}
	}
	check_map_closed(map, x_player, y_player, specs);
}

void	check_map_closed(char **map, int x, int y, t_map_specs *specs)
{
	char	**cpy_map;
	int		i;

	i = 0;
	if (x == -1)
		show_error(map, &ft_free_map, "No player specified in map", specs);
	while (map[i])
		i++;
	cpy_map = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!cpy_map)
		show_error(map, &ft_free_map, NULL, specs);
	while (i--)
	{
		cpy_map[i] = ft_strdup(map[i]);
		if (cpy_map[i] == NULL)
		{
			ft_free_map(cpy_map);
			show_error(map, &ft_free_map, NULL, specs);
		}
	}
	pathfinding(cpy_map, y, x, specs);
	ft_free_map(cpy_map);
}

void	pathfinding(char **map, int i, int j, t_map_specs *specs)
{
	if (map[i][j] == '1' || map[i][j] == 'X')
		return ;
	if (map[i][j] == ' ' || map[i][j] == '\0' || !map[i + 1] || !j || !i)
	{
		ft_free_map(map);
		show_error(map, &ft_free_map, "Map not closed", specs);
	}
	map[i][j] = 'X';
	if (i != 0 && j < (int)ft_strlen(map[i - 1]))
		pathfinding(map, i - 1, j, specs);
	if (j < (int)ft_strlen(map[i + 1]))
		pathfinding(map, i + 1, j, specs);
	if (j > 0)
		pathfinding(map, i, j - 1, specs);
	pathfinding(map, i, j + 1, specs);
}
