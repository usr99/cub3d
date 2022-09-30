/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 21:07:42 by mamartin          #+#    #+#             */
/*   Updated: 2022/09/30 00:10:04 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/window.h"

int		check_comma(char *line, int *i)
{
	while (ft_isdigit(line[*i]))
		(*i)++;
	while (line[*i] == ' ')
		(*i)++;
	if (line[*i] != ',')
		return (-1);
	(*i)++;
	return (0);
}

void	free_specs(t_map_specs *specs)
{
	int i;

	i = 0;
	while (i < 7)
	{
		if (specs->texture[i])
			free(specs->texture[i]);
		i++;
	}
	if (specs->map)
		ft_free_map(specs->map);
	if (specs->sprite)
		free(specs->sprite);
}

void	free_window(t_window window, int exit_code)
{
	int i;

	i = 0;
	while (window.tex[i].img && i < 7)
	{
		mlx_destroy_image(window.mlx, window.tex[i].img);
		i++;
	}
	free_specs(&window.specs);
	free(window.depth_walls);
	mlx_destroy_image(window.mlx, window.world.img);
	if (window.win)
		mlx_destroy_window(window.mlx, window.win);
	exit(exit_code);
}

int		exit_cub3d(t_window *win)
{
	free_window(*win, EXIT_SUCCESS);
	return (0);
}

void	love_norm(int fd, int *i, int *line, int height)
{
	if (fd == -1)
		exit(EXIT_FAILURE);
	*i = 0;
	*line = height - 1;
}
