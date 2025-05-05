/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pos_door_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:03:30 by nmatondo          #+#    #+#             */
/*   Updated: 2025/04/28 11:36:40 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

t_intvector	get_pos_door(t_master *master)
{
	bool		door;
	t_intvector	pos;

	door = more_than_one_door(master);
	if (door)
	{
		pos = get_pos_door_is_in_front_of_the_player(master);
		if (pos.x != -1 && pos.y != -1)
			return (pos);
	}
	return (get_pos_door_around_the_player(master));
}
