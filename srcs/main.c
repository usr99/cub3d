/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 00:56:47 by mamartin          #+#    #+#             */
/*   Updated: 2021/01/12 21:40:51 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parsing.h"
#include "../includes/window.h"

int		main(int ac, char **av)
{
	t_map_specs	specs;
	char		*format;
	int			fd;

	if (ac == 1)
		show_error(NULL, NULL, "Too few arguments", NULL);
	format = ft_strrchr(av[1], '.');
	if (!format || ft_strncmp(format, ".cub", 4) || ft_strlen(format) != 4)
		show_error(NULL, NULL, "File is not a .cub file", NULL);
	if ((fd = open(av[1], O_RDONLY)) == -1)
	{
		perror("Error\nInfo ");
		exit(EXIT_FAILURE);
	}
	init_struct_specs(&specs);
	if (ac > 2 && ft_strlen(av[2]) == 6 && !ft_strncmp(av[2], "--save", 6))
		specs.save = 1;
	parse_map(fd, &specs);
	close(fd);
	create_window(specs);
	return (0);
}

void	init_struct_specs(t_map_specs *specs)
{
	specs->width = 0;
	specs->height = 0;
	specs->texture[0] = NULL;
	specs->texture[1] = NULL;
	specs->texture[2] = NULL;
	specs->texture[3] = NULL;
	specs->texture[4] = NULL;
	specs->sprite = NULL;
	specs->f_color = 0;
	specs->c_color = 0;
	specs->map = NULL;
	specs->save = 0;
}

void	is_specs_completed(t_map_specs *specs, char *line)
{
	if (specs->width == 0)
		show_error(line, &free, "Missing element in .cub file", specs);
	if (specs->height == 0)
		show_error(line, &free, "Missing element in .cub file", specs);
	if (specs->texture[0] == NULL)
		show_error(line, &free, "Missing element in .cub file", specs);
	if (specs->texture[1] == NULL)
		show_error(line, &free, "Missing element in .cub file", specs);
	if (specs->texture[2] == NULL)
		show_error(line, &free, "Missing element in .cub file", specs);
	if (specs->texture[3] == NULL)
		show_error(line, &free, "Missing element in .cub file", specs);
	if (specs->texture[4] == NULL)
		show_error(line, &free, "Missing element in .cub file", specs);
	if (specs->f_color == 0)
		show_error(line, &free, "Missing element in .cub file", specs);
	if (specs->c_color == 0)
		show_error(line, &free, "Missing element in .cub file", specs);
}

void	show_error(void *ptr, void (*del)(void *), char *message,
	t_map_specs *specs)
{
	if (message)
	{
		ft_putstr_fd("Error\nInfo : ", 2);
		ft_putstr_fd(message, 2);
		ft_putchar_fd('\n', 2);
	}
	if (ptr)
		(*del)(ptr);
	if (specs)
		free_specs(specs);
	exit(EXIT_FAILURE);
}
