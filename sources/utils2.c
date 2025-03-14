/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:04:41 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/14 11:34:36 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	ft_countline(char **map)
{
	int	i;

	i = 0;
	if (map == NULL || *map == NULL)
		return (0);
	while (map[i] != NULL)
		i++;
	return (i);
}

int	count_var(char **map, char var)
{
	int	x;
	int	y;
	int	qtd_var;

	qtd_var = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == var)
				qtd_var++;
			x++;
		}
		y++;
	}
	return (qtd_var);
}

t_vector	get_player_pos(char **campus)
{
	int	x;
	int	y;

	x = 0;
	while (campus[x])
	{
		y = 0;
		while (campus[x][y])
		{
			if (campus[x][y] == 'N' || campus[x][y] == 'W'
				|| campus[x][y] == 'E' || campus[x][y] == 'S')
				return ((t_vector){x, y});
			y++;
		}
		x++;
	}
	return ((t_vector){0, 0});
}

t_vector	setdeltadist(t_vector raydir)
{
	t_vector	deltadist;

	if (raydir.x == 0)
	{
		deltadist.x = 1;
		deltadist.y = 0;
	}
	else if (raydir.y == 0)
	{
		deltadist.x = 0;
		deltadist.y = 1;
	}
	else
	{
		deltadist.x = fabs(1 / raydir.x);
		deltadist.y = fabs(1 / raydir.y);
	}
	return (deltadist);
}

t_vector	set_disttoside(t_intvector *step, t_vector raydir,
		t_minilib *render, t_intvector mappos)
{
	t_vector	disttoside;

	if (raydir.x < 0)
	{
		disttoside.x = (render->pos.x - mappos.x) * render->deltadist.x;
		step->x = -1;
	}
	else
	{
		disttoside.x = (mappos.x + 1 - render->pos.x) * render->deltadist.x;
		step->x = 1;
	}
	if (raydir.y < 0)
	{
		disttoside.y = (render->pos.y - mappos.y) * render->deltadist.y;
		step->y = -1;
	}
	else
	{
		disttoside.y = (mappos.y + 1 - render->pos.y) * render->deltadist.y;
		step->y = 1;
	}
	return (disttoside);
}
