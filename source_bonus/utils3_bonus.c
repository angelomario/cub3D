/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:04:41 by aquissan          #+#    #+#             */
/*   Updated: 2025/05/08 15:47:06 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	init_door_data(t_door_data *data)
{
	data->door_hitside = 0;
	data->door_height = 0;
	data->perpendicular_dist_door = 0;
	data->door_map_pos = (t_intvector){0, 0};
}

void	free_door_data(void *data)
{
	t_door_data	*door_data;

	door_data = (t_door_data *)data;
	free(door_data);
}

int	initializedefault_2(t_master *master)
{
	master->view_high = 0;
	master->dimension = (t_3d){0, 2, 0};
	master->time_animation = 0;
	master->limit_time_animation = 10;
	master->door_time_animation = 0;
	master->door_limit_time_animation = 0;
	master->focused_open_door = (t_intvector){-1, -1};
	master->wait_to_close_the_door = 0;
	master->data_root_door = NULL;
	master->root_focused_close_door = NULL;
	master->data_door = NULL;
	master->game_started = false;
	master->type_door = 0;
	master->index_door = 0;
	return (0);
}
