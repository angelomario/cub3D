/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_door_util_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:43:40 by aquissan          #+#    #+#             */
/*   Updated: 2025/04/29 17:43:40 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

bool	door_found(t_master *master, t_intvector pos)
{
	if (master->campus[pos.x][pos.y] == 'D'
		|| master->campus[pos.x][pos.y] == 'd'
		|| master->campus[pos.x][pos.y] == 'F'
		|| master->campus[pos.x][pos.y] == 'f'
		|| master->campus[pos.x][pos.y] == 'G'
		|| master->campus[pos.x][pos.y] == 'g'
		|| master->campus[pos.x][pos.y] == 'H'
		|| master->campus[pos.x][pos.y] == 'h'
		|| master->campus[pos.x][pos.y] == 'J'
		|| master->campus[pos.x][pos.y] == 'j'
		|| master->campus[pos.x][pos.y] == 'K'
		|| master->campus[pos.x][pos.y] == 'k')
		return (true);
	return (false);
}

bool	valid_character_pass(char chr, t_master *master)
{
	if (chr != '1' && chr != 'D' && chr != 'F' && chr != 'G' && chr != 'H'
		&& chr != 'J' && chr != 'K')
	{
		(void)master;
		play_sound(master->sounds.run, 50);
		return (true);
	}
	return (false);
}

static void	is_door(t_master *master, bool *hit, t_intvector *door_map_pos)
{
	t_door_data	*data;

	if (door_found(master, (t_intvector)(*door_map_pos)))
	{
		if (master->data_root_door == NULL)
		{
			master->render.door_object_touched
				= master->campus[(*door_map_pos).x][(*door_map_pos).y];
			master->render.is_door = true;
		}
		data = (t_door_data *)malloc(sizeof(t_door_data) * 1);
		init_door_data(data);
		data->door_hitside = master->door_hitside;
		data->door_map_pos = *door_map_pos;
		ft_lstadd_front(&master->data_root_door, ft_lstnew((void *)data));
	}
	if (master->campus[(*door_map_pos).x][(*door_map_pos).y] == '1')
		*hit = true;
}

void	door_dda(t_master *master, t_intvector *step,
		t_intvector *door_map_pos)
{
	bool		hit;
	t_vector	ddalinesize;

	ddalinesize = (t_vector){master->render.disttoside.x,
		master->render.disttoside.y};
	*door_map_pos = master->render.mappos;
	master->render.is_door = false;
	hit = false;
	while (!hit)
	{
		if (ddalinesize.x < ddalinesize.y)
		{
			(*door_map_pos).x += step->x;
			ddalinesize.x += master->render.deltadist.x;
			master->door_hitside = 0;
		}
		else
		{
			(*door_map_pos).y += step->y;
			ddalinesize.y += master->render.deltadist.y;
			master->door_hitside = 1;
		}
		is_door(master, &hit, door_map_pos);
	}
}

void	set_door_height(t_minilib *render, t_master *master, t_intvector step)
{
	int			len;
	t_door_data	*data;

	len = ft_lstsize(master->data_root_door);
	if (len > 0)
	{
		master->data_door = master->data_root_door;
		while (master->data_door != NULL)
		{
			data = (t_door_data *)master->data_door->content;
			if (data->door_hitside == 0)
				data->perpendicular_dist_door = fabs((data->door_map_pos.x
							- render->pos.x + ((1 - step.x) / 2.0))
						/ render->raydir.x);
			else
				data->perpendicular_dist_door = fabs((data->door_map_pos.y
							- render->pos.y + ((1 - step.y) / 2.0))
						/ render->raydir.y);
			data->door_height = SCREEN_HEIGHT / data->perpendicular_dist_door;
			master->data_door = master->data_door->next;
		}
	}
}
