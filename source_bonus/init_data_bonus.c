/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:47:07 by nmatondo          #+#    #+#             */
/*   Updated: 2025/04/04 08:38:14 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	init_texture(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->textures[i] = NULL;
		data->tex_addr[i] = NULL;
		data->tex_paths[i] = NULL;
		data->tex_width[i] = 0;
		data->tex_height[i] = 0;
		data->tex_endian[i] = 0;
		data->tex_line_length[i] = 0;
		data->tex_bits_per_pixel[i] = 0;
		i++;
	}
}

static void	init_player_texture(t_data *data)
{
	t_3d	dim;

	dim = (t_3d){0, 0, 0};
	while (dim.m < 5)
	{
		dim.l = 0;
		while (dim.l < 3)
		{
			dim.c = 0;
			while (dim.c < 13)
			{
				data->player_texture[dim.m][dim.l][dim.c] = NULL;
				data->player_texture_addr[dim.m][dim.l][dim.c] = NULL;
				data->player_texture_paths[dim.m][dim.l][dim.c] = NULL;
				data->player_texture_width[dim.m][dim.l][dim.c] = 0;
				data->player_texture_height[dim.m][dim.l][dim.c] = 0;
				data->player_texture_endian[dim.m][dim.l][dim.c] = 0;
				data->player_texture_line_length[dim.m][dim.l][dim.c] = 0;
				data->player_texture_bits_per_pixel[dim.m][dim.l][dim.c] = 0;
				dim.c++;
			}
			dim.l++;
		}
		dim.m++;
	}
}

static void	init_door_texture(t_data *data)
{
	int	l;
	int	i;

	l = 0;
	while (l < 3)
	{
		i = 0;
		while (i < 13)
		{
			data->door_texture[l][i] = NULL;
			data->door_texture_addr[l][i] = NULL;
			data->door_texture_paths[l][i] = NULL;
			data->door_texture_width[l][i] = 0;
			data->door_texture_height[l][i] = 0;
			data->door_texture_endian[l][i] = 0;
			data->door_texture_line_length[l][i] = 0;
			data->door_texture_bits_per_pixel[l][i] = 0;
			i++;
		}
		l++;
	}
}

void	init_data_struct(t_data *data)
{
	if (!data)
		return ;
	data->img = NULL;
	data->addr = NULL;
	data->bits_per_pixel = 0;
	data->line_length = 0;
	data->endian = 0;
	init_texture(data);
	init_player_texture(data);
	init_door_texture(data);
}
