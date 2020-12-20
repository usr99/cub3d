/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 13:02:50 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/20 17:39:24 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/window.h"

void	create_window(t_map_specs specs)
{
	void *mlx;
	void *win;

	if (!(mlx = mlx_init()))
		exit(EXIT_FAILURE);
	if (!(win = mlx_new_window(mlx, specs.width, specs.height, "CUB3D")))
		exit(EXIT_FAILURE);
	display_floor_and_sky(mlx, win, specs);
	raycast(mlx, win, specs);
	mlx_loop(mlx);
}

void	display_floor_and_sky(void *mlx, void *win, t_map_specs specs)
{
	t_data_img	sky;
	t_data_img	floor;
	int			i;
	int			nb_pixels_img;

	sky.img = mlx_new_image(mlx, specs.width, specs.height / 2);
	floor.img = mlx_new_image(mlx, specs.width, specs.height / 2);
	if (sky.img == NULL || floor.img == NULL)
		exit(EXIT_FAILURE);
	nb_pixels_img = specs.width * (specs.height / 2);
	sky.addr = (unsigned int *)mlx_get_data_addr(sky.img, &sky.bpp, &sky.size_line,
		&sky.endian);
	floor.addr = (unsigned int *)mlx_get_data_addr(floor.img, &floor.bpp, &floor.size_line,
		&floor.endian);
	i = -1;
	while (++i < nb_pixels_img)
		sky.addr[i] = specs.c_color;
	i = -1;
	while (++i < nb_pixels_img)
		floor.addr[i] = specs.f_color;
	mlx_put_image_to_window(mlx, win, sky.img, 0, 0);
	mlx_put_image_to_window(mlx, win, floor.img, 0, specs.height / 2);
}

void	raycast(void *mlx, void *win, t_map_specs specs)
{
	double	posX, posY;
	double	dirX = 0, dirY = 0;
	double	planeX, planeY;
	int		i = 0;
	int		x = 0;
	int		j;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	deltaDistX;
	double	deltaDistY;
	double	sideDistX;
	double	sideDistY;
	int		hit;
	int		side;
	int		stepX;
	int		stepY;
	double	distWall;
	int		lineHeight;
	int		bottomLine;
	int		topLine;
	int		color;

	// get player position and direction
	while (specs.map[i])
	{
		j = 0;
		while (specs.map[i][j])
		{
			if (ft_strchr("NSWE", specs.map[i][j]))
			{
				if (specs.map[i][j] == 'N')
					dirY = -1.0;
				else if (specs.map[i][j] == 'S')
					dirY = 1.0;
				else if (specs.map[i][j] == 'W')
					dirX = -1.0;
				else if (specs.map[i][j] == 'E')
					dirX = 1.0;
				posX = (double)j + 0.5;
				posY = (double)i + 0.5;
			}
			j++;
		}
		i++;
	}
	// set plan vector as FOV = 66°
	if (dirX)
		planeY = 0.66;
	else if (dirY)
		planeX = 0.66;

	// Raycasting loop
	while (x < specs.width)
	{
		// get ray vector
		cameraX = 2 * x / (double)specs.width - 1;
		rayDirX = dirX + planeX * cameraX;
		rayDirY = dirY + planeY * cameraX;
		
		// set ray at player position
		mapX = (int)posX;
		mapY = (int)posY;

		// get the distance the ray has to travel to go from one side to the other
		deltaDistX = fabs(1 / rayDirX);
      	deltaDistY = fabs(1 / rayDirY);

		// get distance from next side
		// set direction the ray move inside the map
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (mapX - posX + 1.0) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX - posX + 1.0) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (mapY - posY + 1.0) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY - posY + 1.0) * deltaDistY;
		}

		hit = 0;
		// move the ray forward until he hits a wall
		while (!hit)
		{
			// if the next side is a x-side
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			// if this is the side of a wall
			if (specs.map[mapY][mapX] == '1')
				hit = 1;
		}

		// get wall distance from camera plane (not from the player position to avoid fisheye effect)
		if (side == 0)
			distWall = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			distWall = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		// get the height of the line we will draw later
		lineHeight = specs.height / distWall;
		// get the coordinate of the bottom of the line
		bottomLine = -lineHeight / 2 + specs.height / 2;
		if (bottomLine < 0)
			bottomLine = 0;
		// and the top of the line
		topLine = lineHeight / 2 + specs.height / 2;
		if (topLine > specs.height)
			topLine = specs.height;

		// darker color if it's a y-side
		if (side == 0)
			color = 0x80A1C1;
		else
			color = 0x436689;

		// draw line
		for (int y = bottomLine ; y < topLine ; y++)
			mlx_pixel_put(mlx, win, x, y, color);
		x++;
	}	
}
