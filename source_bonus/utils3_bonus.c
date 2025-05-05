/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:04:41 by aquissan          #+#    #+#             */
/*   Updated: 2025/04/21 10:52:48 by nmatondo         ###   ########.fr       */
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
