/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_animation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:03:30 by nmatondo          #+#    #+#             */
/*   Updated: 2025/05/09 14:09:04 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

char	get_next_image_state(t_master *master, t_intvector focused_door)
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
		if (list[index] == master->campus[focused_door.x][focused_door.y])
			break ;
		index++;
	}
	return (list[index + 1]);
}

static void	reset_status_animation_open_the_door(t_master *master)
{
	t_intvector	*focused_close_door;

	focused_close_door = (t_intvector *)malloc(1 * sizeof(t_intvector));
	focused_close_door->x = master->focused_open_door.x;
	focused_close_door->y = master->focused_open_door.y;
	ft_lstadd_back(&master->root_focused_close_door,
		ft_lstnew((void *)focused_close_door));
	master->focused_open_door = (t_intvector){-1, -1};
	master->keyboard.open_door = false;
	master->keyboard.close_door = true;
	master->wait_to_close_the_door = 80;
}

void	animation_open_the_door(t_master *master)
{
	char		chr;
	t_intvector	pos;

	if (master->keyboard.open_door)
		master->door_limit_time_animation = 2;
	if (master->keyboard.open_door)
	{
		if (master->door_time_animation >= master->door_limit_time_animation)
		{
			play_sound(master->sounds.door_open, 50, NO_RESTART);
			pos = get_pos_door(master);
			if (master->focused_open_door.x == -1
				&& master->focused_open_door.y == -1)
				master->focused_open_door = pos;
			chr = get_next_image_state(master, master->focused_open_door);
			if (chr)
				master->campus[master->focused_open_door.x]
				[master->focused_open_door.y] = chr;
			else
				reset_status_animation_open_the_door(master);
			master->door_time_animation = 0;
		}
		else
			master->door_time_animation++;
	}
}
