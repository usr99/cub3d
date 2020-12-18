/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:03:47 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/17 23:06:06 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_map(void *ptr)
{
	char	**map;
	int		i;

	i = 0;
	map = (char **)ptr;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
