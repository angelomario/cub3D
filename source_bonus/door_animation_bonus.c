/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_animation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:03:30 by nmatondo          #+#    #+#             */
/*   Updated: 2025/05/03 19:20:45 by aquissan         ###   ########.fr       */
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

char	get_back_image_state(t_master *master, t_intvector focused_door)
{
	int		index;
	char	*list;

	play_sound(master->sounds.door_close, 50);
	if (master->type_door == 0)
		list = door_one_character_list();
	else if (master->type_door == 1)
		list = door_two_character_list();
	else if (master->type_door == 2)
		list = door_three_character_list();
	index = ft_strlen(list) - 1;
	while (index > -1 && list[index])
	{
		if (list[index] == master->campus[focused_door.x][focused_door.y])
			break ;
		index--;
	}
	return (list[index - 1]);
}

static void	reset_status_animation_open_the_door(t_master *master)
{
	master->focused_close_door = master->focused_open_door;
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
			play_sound(master->sounds.door_open, 50);
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

void	animation_close_the_door(t_master *master)
{
	char	chr;

	if (master->keyboard.close_door && master->wait_to_close_the_door != 0)
		master->wait_to_close_the_door--;
	if (master->keyboard.close_door && master->wait_to_close_the_door == 0
		&& master->campus[(int)master->render.pos.x][(int)master->render.pos.y]
		!= master->campus[master->focused_close_door.x]
			[master->focused_close_door.y])
	{
		if (master->door_time_animation >= master->door_limit_time_animation)
		{
			chr = get_back_image_state(master, master->focused_close_door);
			if (chr != 0)
				master->campus[master->focused_close_door.x][
					master->focused_close_door.y] = chr;
			else
			{
				master->focused_close_door = (t_intvector){-1, -1};
				master->keyboard.close_door = false;
			}
			master->door_time_animation = 0;
		}
		else
			master->door_time_animation++;
	}
}
