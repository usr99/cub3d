/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 00:56:47 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/17 16:55:00 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	print_map(t_map_specs specs)
{
	printf("= SPECS ===================\n");
	printf("width = %d\n", specs.width);
	printf("height = %d\n", specs.height);
	printf("no = %s\n", specs.no_texture);
	printf("so = %s\n", specs.so_texture);
	printf("we = %s\n", specs.we_texture);
	printf("ea = %s\n", specs.ea_texture);
	printf("s = %s\n", specs.s_texture);
	printf("f_color = %d,%d,%d\n", (specs.f_color >> 16) & 0xFF, (specs.f_color >> 8) & 0xFF, specs.f_color & 0xFF);
	printf("c_color = %d,%d,%d\n", (specs.c_color >> 16) & 0xFF, (specs.c_color >> 8) & 0xFF, specs.c_color & 0xFF);
}

int		main(int ac, char **av)
{
	t_map_specs	specs;
	int			fd;

	if (ac == 1)
		show_error(NULL, TOO_FEW_ARG);
	if ((fd = open(av[1], O_RDONLY)) == -1)
	{
		perror("Error\nInfo ");
		exit(EXIT_FAILURE);
	}
	init_struct_specs(&specs);
	parse_map(fd, &specs);
	//print_map(specs);
	return (0);
}

void	init_struct_specs(t_map_specs *specs)
{
	specs->width = 0;
	specs->height = 0;
	specs->no_texture = NULL;
	specs->so_texture = NULL;
	specs->we_texture = NULL;
	specs->ea_texture = NULL;
	specs->s_texture = NULL;
	specs->f_color = 0;
	specs->c_color = 0;
	specs->map = NULL;
}

void	is_specs_completed(t_map_specs *specs, char *line)
{
	if (specs->width == 0)
		show_error(line, MISSING_VALUE);
	if (specs->height == 0)
		show_error(line, MISSING_VALUE);
	if (specs->no_texture == NULL)
		show_error(line, MISSING_VALUE);
	if (specs->so_texture == NULL)
		show_error(line, MISSING_VALUE);
	if (specs->we_texture == NULL)
		show_error(line, MISSING_VALUE);
	if (specs->ea_texture == NULL)
		show_error(line, MISSING_VALUE);
	if (specs->s_texture == NULL)
		show_error(line, MISSING_VALUE);
	if (specs->f_color == 0)
		show_error(line, MISSING_VALUE);
	if (specs->c_color == 0)
		show_error(line, MISSING_VALUE);
}

void	show_error(void *ptr, t_error id_error)
{
	if (id_error == TOO_FEW_ARG)
		ft_putstr_fd("Error\nInfo : Too few arguments\n", 2);
	else if (id_error == READ_FILE)
		ft_putstr_fd("Error\nInfo : Can't read file\n", 2);
	else if (id_error == INVALID_FILE)
		ft_putstr_fd("Error\nInfo : Invalid .cub file\n", 2);
	else if (id_error == MISSING_MAP)
		ft_putstr_fd("Error\nInfo : Map description missing/incorrect\n", 2);
	else if (id_error == MISSING_VALUE)
		ft_putstr_fd("Error\nInfo : Missing element in .cub file\n", 2);
	else if (id_error == BAD_RGB_VALUE)
		ft_putstr_fd("Error\nInfo : Bad value for color\n", 2);
	else if (id_error == ALREADY_RES)
		ft_putstr_fd("Error\nInfo : Resolution is set twice\n", 2);
	else if (id_error == BAD_RES_VALUE)
		ft_putstr_fd("Error\nInfo : Bad value for resolution\n", 2);
	else if (id_error == BAD_MAP)
		ft_putstr_fd("Error\nInfo : Bad character in map description\n", 2);
	else if (id_error == PLAYER_TWICE)
		ft_putstr_fd("Error\nInfo : Player position is set twice\n", 2);
	else if (id_error == MAP_NOT_CLOSED)
		ft_putstr_fd("Error\nInfo : Map not closed\n", 2);
	if (ptr)
		free(ptr);
	exit(EXIT_FAILURE);
}

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
