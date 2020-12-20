/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamartin <mamartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 19:11:29 by mamartin          #+#    #+#             */
/*   Updated: 2020/12/20 19:26:07 by mamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/keysym.h>
#include "../includes/window.h"

int	handle_event(int keycode, t_window *window)
{
	if (keycode == XK_Up)
		printf("HAUT\n");
	else if (keycode == XK_Down)
		printf("BAS\n");
	else if (keycode == XK_Right)
		printf("DROITE\n");
	else if (keycode == XK_Left)
		printf("GAUCHE\n");
	return (0);
}