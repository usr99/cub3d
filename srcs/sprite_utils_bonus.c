/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 18:00:56 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/27 18:01:19 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sprite.h"

t_vector	*get_sprite_coordinates(char **map)
{
	t_vector	*sprite;
	int			nb_sprites;
	int			i;
	int			j;

	i = 0;
	nb_sprites = 0;
	sprite = NULL;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
			{
				nb_sprites++;
				sprite = get_sprite(sprite, nb_sprites);
				sprite[nb_sprites - 1].x = j + 0.5;
				sprite[nb_sprites - 1].y = i + 0.5;
			}
			j++;
		}
		i++;
	}
	return (sprite);
}

t_vector	*get_sprite(t_vector *sprite, int nb_sprites)
{
	t_vector	*tmp;
	int			i;

	i = 0;
	tmp = sprite;
	sprite = (t_vector *)ft_calloc(nb_sprites + 1, sizeof(t_vector));
	if (!sprite)
		exit(EXIT_FAILURE);
	if (tmp)
	{
		while (i < nb_sprites - 1)
		{
			sprite[i] = tmp[i];
			i++;
		}
		free(tmp);
	}
	sprite[nb_sprites].x = -1;
	sprite[nb_sprites].y = -1;
	return (sprite);
}
