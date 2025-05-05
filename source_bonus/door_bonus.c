/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:33:12 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/20 15:33:38 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	check_door(char **campus)
{
	int	x;
	int	y;

	y = -1;
	while (campus && campus[++y])
	{
		x = -1;
		while (campus[y] && campus[y][++x])
		{
			if (campus[y][x] == 'D' || campus[y][x] == 'd')
			{
				if ((x > 0 && campus[y][x - 1] == '1') && (campus[y][x + 1]
						&& campus[y][x + 1] == '1'))
					x += 0;
				else if ((y > 0 && campus[y - 1][x] == '1') && (campus[y + 1][x]
						&& campus[y + 1][x] == '1'))
					x += 0;
				else
					return (1);
				if (check_around(campus, y, x) == 0)
					return (1);
			}
		}
	}
	return (0);
}
