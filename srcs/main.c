/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 00:56:47 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/18 12:51:25 by mamartin         ###   ########.fr       */
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
		show_error(NULL, NULL, "Too few arguments");
	if ((fd = open(av[1], O_RDONLY)) == -1)
	{
		perror("Error\nInfo ");
		exit(EXIT_FAILURE);
	}
	init_struct_specs(&specs);
	parse_map(fd, &specs);
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
		show_error(line, &free, "Missing element in .cub file");
	if (specs->height == 0)
		show_error(line, &free, "Missing element in .cub file");
	if (specs->no_texture == NULL)
		show_error(line, &free, "Missing element in .cub file");
	if (specs->so_texture == NULL)
		show_error(line, &free, "Missing element in .cub file");
	if (specs->we_texture == NULL)
		show_error(line, &free, "Missing element in .cub file");
	if (specs->ea_texture == NULL)
		show_error(line, &free, "Missing element in .cub file");
	if (specs->s_texture == NULL)
		show_error(line, &free, "Missing element in .cub file");
	if (specs->f_color == 0)
		show_error(line, &free, "Missing element in .cub file");
	if (specs->c_color == 0)
		show_error(line, &free, "Missing element in .cub file");
}

void	show_error(void *ptr, void (*del)(void *), char *message)
{
	if (message)
	{
		ft_putstr_fd("Error\nInfo : ", 2);
		ft_putstr_fd(message, 2);
		ft_putchar_fd('\n', 2);
	}
	if (ptr)
		(*del)(ptr);
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
