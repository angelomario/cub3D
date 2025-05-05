/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pos_door_util_1_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:03:30 by nmatondo          #+#    #+#             */
/*   Updated: 2025/04/16 13:32:26 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

bool	four_doors(t_master *master)
{
	if (master->campus[(int)master->render.pos.x + 1]
		[(int)master->render.pos.y] == 'D'
		&& master->campus[(int)master->render.pos.x - 1]
		[(int)master->render.pos.y] == 'D'
		&& master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y + 1] == 'D'
		&& master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y - 1] == 'D')
		return (true);
	return (false);
}

static bool	three_doors_2(t_master *master)
{
	if (master->campus[(int)master->render.pos.x + 1]
		[(int)master->render.pos.y] == 'D'
		&& master->campus[(int)master->render.pos.x - 1]
		[(int)master->render.pos.y] == 'D'
		&& master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y + 1] != 'D'
		&& master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y - 1] == 'D')
		return (true);
	if (master->campus[(int)master->render.pos.x + 1]
		[(int)master->render.pos.y] == 'D'
		&& master->campus[(int)master->render.pos.x - 1]
		[(int)master->render.pos.y] == 'D'
		&& master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y + 1] == 'D'
		&& master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y - 1] != 'D')
		return (true);
	return (false);
}

bool	three_doors(t_master *master)
{
	if (master->campus[(int)master->render.pos.x + 1]
		[(int)master->render.pos.y] != 'D'
		&& master->campus[(int)master->render.pos.x - 1]
		[(int)master->render.pos.y] == 'D'
		&& master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y + 1] == 'D'
		&& master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y - 1] == 'D')
		return (true);
	if (master->campus[(int)master->render.pos.x + 1]
		[(int)master->render.pos.y] == 'D'
		&& master->campus[(int)master->render.pos.x - 1]
		[(int)master->render.pos.y] != 'D'
		&& master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y + 1] == 'D'
		&& master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y - 1] == 'D')
		return (true);
	return (three_doors_2(master));
}

static bool	two_doors_2(t_master *master)
{
	if (master->campus[(int)master->render.pos.x - 1]
		[(int)master->render.pos.y] == 'D'
		&& master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y + 1] == 'D')
		return (true);
	if (master->campus[(int)master->render.pos.x + 1]
		[(int)master->render.pos.y] == 'D'
		&& master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y - 1] == 'D')
		return (true);
	if (master->campus[(int)master->render.pos.x + 1]
		[(int)master->render.pos.y] == 'D'
		&& master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y + 1] == 'D')
		return (true);
	return (false);
}

bool	two_doors(t_master *master)
{
	if (master->campus[(int)master->render.pos.x + 1]
		[(int)master->render.pos.y] == 'D'
		&& master->campus[(int)master->render.pos.x - 1]
		[(int)master->render.pos.y] == 'D')
		return (true);
	if (master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y + 1] == 'D'
		&& master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y - 1] == 'D')
		return (true);
	if (master->campus[(int)master->render.pos.x - 1]
		[(int)master->render.pos.y] == 'D'
		&& master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y - 1] == 'D')
		return (true);
	return (two_doors_2(master));
}
