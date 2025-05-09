/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_door_image_index_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:50:40 by nmatondo          #+#    #+#             */
/*   Updated: 2025/05/08 11:57:03 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

bool	player_near_the_door(t_master *master)
{
	if (master->campus[(int)master->render.pos.x + 1]
		[(int)master->render.pos.y] == 'D')
		return (true);
	if (master->campus[(int)master->render.pos.x - 1]
		[(int)master->render.pos.y] == 'D')
		return (true);
	if (master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y + 1] == 'D')
		return (true);
	if (master->campus[(int)master->render.pos.x]
		[(int)master->render.pos.y - 1] == 'D')
		return (true);
	return (false);
}

char	*door_one_character_list(void)
{
	static char	character[] = {'D', 'F', 'G', 'H', 'J', 'K', 'k',
		'j', 'h', 'g', 'f', 'd', '\0'};

	return (character);
}

char	*door_two_character_list(void)
{
	static char	character[] = {'D', 'F', 'G', 'H', 'J',
		'j', 'h', 'g', 'f', 'd', '\0'};

	return (character);
}

char	*door_three_character_list(void)
{
	static char	character[] = {'D', 'F', 'G', 'H', 'h', 'g', 'f', 'd', '\0'};

	return (character);
}

int	get_image_index_by_character_type(t_master *master, char chr)
{
	int		index;
	char	*list;

	index = 0;
	if (master->type_door == 0)
		list = door_one_character_list();
	else if (master->type_door == 1)
		list = door_two_character_list();
	else if (master->type_door == 2)
		list = door_three_character_list();
	while (list[index])
	{
		if (list[index] == chr)
			return (index);
		index++;
	}
	return (index);
}
