/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 17:46:35 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/27 18:21:50 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/window.h"
#include "../includes/raycasting.h"

t_wall	raycast(t_player player, t_map_specs specs, int x)
{
	double	camera;
	t_ray	ray;
	t_wall	wall;

	camera = 2 * x / (double)specs.width - 1;
	ray.dir.x = player.x_dir + player.x_plane * camera;
	ray.dir.y = player.y_dir + player.y_plane * camera;
	ray.map.x = (int)player.x_pos;
	ray.map.y = (int)player.y_pos;
	get_ray_data(player, &ray);
	find_wall(player, specs, ray, &wall);
	get_wall_data(player, ray, &wall);
	return (wall);
}

void	get_ray_data(t_player player, t_ray *ray)
{
	if (ray->dir.y == 0)
		ray->delta.x = 0;
	else
	{
		if (ray->dir.x == 0)
			ray->delta.x = 1;
		else
			ray->delta.x = fabs(1 / ray->dir.x);
	}
	if (ray->dir.x == 0)
		ray->delta.y = 0;
	else
	{
		if (ray->dir.y == 0)
			ray->delta.y = 1;
		else
			ray->delta.y = fabs(1 / ray->dir.y);
	}
	get_ray_step(player, ray);
}

void	get_ray_step(t_player player, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side.x = (player.x_pos - ray->map.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side.x = (ray->map.x - player.x_pos + 1.0) * ray->delta.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side.y = (player.y_pos - ray->map.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side.y = (ray->map.y - player.y_pos + 1.0) * ray->delta.y;
	}
}

void	find_wall(t_player pl, t_map_specs specs, t_ray ray, t_wall *wall)
{
	int		hit;

	hit = 0;
	while (!hit)
	{
		if (ray.side.x < ray.side.y)
		{
			ray.side.x += ray.delta.x;
			ray.map.x += ray.step.x;
			wall->side = 0;
		}
		else
		{
			ray.side.y += ray.delta.y;
			ray.map.y += ray.step.y;
			wall->side = 1;
		}
		if (specs.map[ray.map.y][ray.map.x] == '1')
			hit = 1;
	}
	if (wall->side == 0)
		wall->dist = (ray.map.x - pl.x_pos + (1 - ray.step.x) / 2) / ray.dir.x;
	else
		wall->dist = (ray.map.y - pl.y_pos + (1 - ray.step.y) / 2) / ray.dir.y;
	wall->height = specs.height / wall->dist;
}

void	get_wall_data(t_player player, t_ray ray, t_wall *wall)
{
	if (wall->side == 0)
	{
		if (ray.dir.x < 0)
			wall->side = 3;
		else
			wall->side = 2;
		wall->x = player.y_pos + wall->dist * ray.dir.y;
	}
	else
	{
		if (ray.dir.y < 0)
			wall->side = 1;
		else
			wall->side = 0;
		wall->x = player.x_pos + wall->dist * ray.dir.x;
	}
	wall->x -= floor(wall->x);
}
