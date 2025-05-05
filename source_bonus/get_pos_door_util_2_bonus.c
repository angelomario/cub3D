/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pos_door_util_2_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:03:30 by nmatondo          #+#    #+#             */
/*   Updated: 2025/05/05 13:17:59 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

bool	more_than_one_door(t_master *master)
{
	bool	door;

	door = four_doors(master);
	if (door)
		return (door);
	door = three_doors(master);
	if (door)
		return (door);
	door = two_doors(master);
	if (door)
		return (door);
	return (false);
}

static t_intvector	north_south_door(t_master *master)
{
	if (master->render.raydir.y > 0)
	{
		if (master->campus[(int)master->render.pos.x]
			[(int)master->render.pos.y + 1] == 'D')
			return ((t_intvector){(int)master->render.pos.x,
				(int)master->render.pos.y + 1});
	}
	else
	{
		if (master->campus[(int)master->render.pos.x]
			[(int)master->render.pos.y - 1] == 'D')
			return ((t_intvector){(int)master->render.pos.x,
				(int)master->render.pos.y - 1});
	}
	return ((t_intvector){-1, -1});
}

static t_intvector	east_west_door(t_master *master)
{
	if (master->render.raydir.x > 0)
	{
		if (master->campus[(int)master->render.pos.x + 1]
			[(int)master->render.pos.y] == 'D')
			return ((t_intvector){(int)master->render.pos.x + 1,
				(int)master->render.pos.y});
	}
	else
	{
		if (master->campus[(int)master->render.pos.x - 1]
			[(int)master->render.pos.y] == 'D')
			return ((t_intvector){(int)master->render.pos.x - 1,
				(int)master->render.pos.y});
	}
	return ((t_intvector){-1, -1});
}

t_intvector	get_pos_door_is_in_front_of_the_player(
	t_master *master)
{
	t_intvector	pos;

	if (master->door_hitside == 1)
	{
		pos = east_west_door(master);
		if (pos.x != -1 && pos.y != -1)
			return (pos);
	}
	else
	{
		pos = north_south_door(master);
		if (pos.x != -1 && pos.y != -1)
			return (pos);
	}
	return ((t_intvector){-1, -1});
}

t_intvector	get_pos_door_around_the_player(t_master *master)
{
	if (master->campus[(int)master->render.pos.x + 1]
		[(int)master->render.pos.y] == 'D')
		return ((t_intvector){(int)master->render.pos.x + 1,
			(int)master->render.pos.y});
	if (master->campus[(int)master->render.pos.x - 1]
		[(int)master->render.pos.y] == 'D')
		return ((t_intvector){(int)master->render.pos.x - 1,
			(int)master->render.pos.y});
	if (master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y + 1] == 'D')
		return ((t_intvector){(int)master->render.pos.x,
			(int)master->render.pos.y + 1});
	if (master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y - 1] == 'D')
		return ((t_intvector){(int)master->render.pos.x,
			(int)master->render.pos.y - 1});
	return ((t_intvector){-1, -1});
}
