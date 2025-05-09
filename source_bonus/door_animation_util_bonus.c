/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_animation_util_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 10:42:39 by nmatondo          #+#    #+#             */
/*   Updated: 2025/05/09 14:09:10 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	free_root_focused_close_door(t_master *master)
{
	t_list		*aux;
	t_intvector	*content;

	while (master->root_focused_close_door != NULL)
	{
		content = master->root_focused_close_door->content;
		aux = master->root_focused_close_door;
		master->root_focused_close_door
			= master->root_focused_close_door->next;
		free(content);
		free(aux);
	}
	master->root_focused_close_door = NULL;
}

char	get_back_image_state(t_master *master, t_intvector *focused_door)
{
	int		index;
	char	*list;

	play_sound(master->sounds.door_close, 50, NO_RESTART);
	if (master->type_door == 0)
		list = door_one_character_list();
	else if (master->type_door == 1)
		list = door_two_character_list();
	else if (master->type_door == 2)
		list = door_three_character_list();
	index = ft_strlen(list) - 1;
	while (index > -1 && list[index])
	{
		if (list[index] == master->campus[focused_door->x][focused_door->y])
			break ;
		index--;
	}
	return (list[index - 1]);
}

void	animation_close_the_door_util(t_master *master,
	t_intvector *focused_close_door)
{
	char		chr;
	t_list		*aux;

	if (master->door_time_animation >= master->door_limit_time_animation)
	{
		chr = get_back_image_state(master, focused_close_door);
		if (chr != 0)
			master->campus[focused_close_door->x][focused_close_door->y] = chr;
		else
		{
			free(focused_close_door);
			aux = master->root_focused_close_door;
			master->root_focused_close_door
				= master->root_focused_close_door->next;
			free(aux);
			if (ft_lstsize(master->root_focused_close_door) == 0)
				master->keyboard.close_door = false;
			else
				master->wait_to_close_the_door = 40;
		}
		master->door_time_animation = 0;
	}
	else
		master->door_time_animation++;
}

void	animation_close_the_door(t_master *master)
{
	t_intvector	*focused_close_door;

	if (master->keyboard.close_door && master->wait_to_close_the_door != 0)
		master->wait_to_close_the_door--;
	if (master->keyboard.close_door
		&& master->wait_to_close_the_door == 0)
	{
		focused_close_door
			= (t_intvector *)master->root_focused_close_door->content;
		if (master->campus[(int)master->render.pos.x][(int)master->render.pos.y]
			!= master->campus[focused_close_door->x][focused_close_door->y])
			animation_close_the_door_util(master, focused_close_door);
	}
}
