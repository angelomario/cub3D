/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_crosshair_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 12:34:44 by nmatondo          #+#    #+#             */
/*   Updated: 2025/04/04 08:02:52 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	draw_crosshair(t_master *master)
{
	int	y;
	int	x;

	y = 0;
	while (y < 3)
	{
		x = 0;
		while (x < 3)
		{
			my_mlx_pixel_put(&master->img,
				(SCREEN_WIDTH / 2) + x, (SCREEN_HEIGHT / 2) + y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}
