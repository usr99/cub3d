/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:11:02 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/18 12:51:20 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == '0')
				printf("\033[34;44m" "%c", map[i][j]);
			else if (map[i][j] == 'X')
				printf("\033[33;43m" "%c", map[i][j]);
			else if (map[i][j] == '1')
				printf("\033[31;41m" "%c", map[i][j]);
			else if (map[i][j] == '2')
				printf("\033[32;42m" "%c", map[i][j]);
			else if (ft_strchr("NSWE", map[i][j]))
				printf("\033[30;44m" "%c", map[i][j]);
			else
				printf("%c", map[i][j]);
			printf("\033[0m");
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}
}

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
					show_error(map, &ft_free_map, "Player location set twice");
				x_player = j;
				y_player = i;
			}
			else if (!ft_strchr(" 012", map[i][j]))
				show_error(map, &ft_free_map, "Bad character in map");
			j++;
		}
	}
	check_map_closed(map, x_player, y_player);
}

void	check_map_closed(char **map, int x, int y)
{
	char	**cpy_map;
	int		i;

	i = 0;
	if (x == -1)
		show_error(map, &ft_free_map, "No player specified in map");
	while (map[i])
		i++;
	cpy_map = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!cpy_map)
		show_error(map, &ft_free_map, NULL);
	while (i--)
	{
		cpy_map[i] = ft_strdup(map[i]);
		if (cpy_map[i] == NULL)
		{
			ft_free_map(cpy_map);
			show_error(map, &ft_free_map, NULL);
		}
	}
	pathfinding(cpy_map, y, x);
	print_(cpy_map);
	ft_free_map(cpy_map);
}

void	pathfinding(char **map, int i, int j)
{
	if (map[i][j] == '1' || map[i][j] == 'X')
		return ;
	if (map[i][j] == ' ' || map[i][j] == '\0' || !map[i + 1] || !j || !i)
	{
		ft_free_map(map);
		show_error(map, &ft_free_map, "Map not closed");
	}
	map[i][j] = 'X';
	if (i != 0 && j < (int)ft_strlen(map[i - 1]))
		pathfinding(map, i - 1, j);
	if (j < (int)ft_strlen(map[i + 1]))
		pathfinding(map, i + 1, j);
	if (j > 0)
		pathfinding(map, i, j - 1);
	pathfinding(map, i, j + 1);
}
