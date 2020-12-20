/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:46:35 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/20 19:28:57 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/window.h"
#include "../includes/raycasting.h"

int	raycast(t_player player, t_map_specs specs, int x, int *color)
{
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

	// get ray vector
	cameraX = 2 * x / (double)specs.width - 1;
	rayDirX = player.dirX + player.planeX * cameraX;
	rayDirY = player.dirY + player.planeY * cameraX;
	
	// set ray at player position
	mapX = (int)player.posX;
	mapY = (int)player.posY;

	// get the distance the ray has to travel to go from one side to the other
	deltaDistX = fabs(1 / rayDirX);
    deltaDistY = fabs(1 / rayDirY);

	// get distance from next side
	// set direction the ray move inside the map
	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (mapX - player.posX + 1.0) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX - player.posX + 1.0) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (mapY - player.posY + 1.0) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY - player.posY + 1.0) * deltaDistY;
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
		distWall = (mapX - player.posX + (1 - stepX) / 2) / rayDirX;
	else
		distWall = (mapY - player.posY + (1 - stepY) / 2) / rayDirY;

	if (side == 0)
		*color = 0x80A1C1;
	else
		*color = 0x436689;

	return (specs.height / distWall);
}
