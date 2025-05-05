/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_door_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:32:11 by aquissan          #+#    #+#             */
/*   Updated: 2025/04/21 11:20:22 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

unsigned int	get_door_color(t_master *master, t_texture *texture,
		t_data *img)
{
	unsigned int	color;

	(void)master;
	color = *(unsigned int *)(img->door_texture_addr[master->type_door]
		[master->index_door] + (texture->y * img->door_texture_line_length
			[master->type_door][master->index_door] + texture->x
				* (img->door_texture_bits_per_pixel[master->type_door]
				[master->index_door] / 8)));
	return (color);
}

int	get_x_coordinate_door_texture(int hitSide, t_master *master, t_data *img)
{
	int			texx;
	double		wallx;
	t_door_data	*data;

	data = (t_door_data *)master->data_door->content;
	if (hitSide == 0)
		wallx = master->render.pos.y
			+ data->perpendicular_dist_door * master->render.raydir.y;
	else
		wallx = master->render.pos.x
			+ data->perpendicular_dist_door * master->render.raydir.x;
	wallx -= floor(wallx);
	texx = (int)(wallx * (double)img->door_texture_width
		[master->type_door][master->index_door]);
	if ((hitSide == 0 && master->render.raydir.x > 0)
		|| (hitSide == 1 && master->render.raydir.y < 0))
		texx = img->door_texture_width[master->type_door][master->index_door]
			- texx - 1;
	return (texx);
}

static double	get_pos_texture_door(
	t_door_data *data, t_master *master, t_draw_door *draw)
{
	return (((draw->start_door - master->view_high) - SCREEN_HEIGHT
			/ 2 + data->door_height / 2) * draw->texture_door.step);
}

static void	draw_door_texture_in_draw_door(
	t_intvector *pos, t_data *img, t_master *master, t_draw_door *draw)
{	
	t_door_data	*data;

	data = (t_door_data *)master->data_door->content;
	draw->start_door = get_draw_start_position(data->door_height, master);
	draw->end_door = get_draw_end_position(data->door_height, master);
	draw->texture_door.index = 0;
	draw->texture_door.x = get_x_coordinate_door_texture(
			data->door_hitside, master, img);
	draw->texture_door.step = 1.0 * img->door_texture_height[master->type_door]
	[master->index_door] / data->door_height;
	draw->texture_door.pos = get_pos_texture_door(data, master, draw);
	pos->y = draw->start_door;
	while (pos->y < draw->end_door)
	{
		draw->texture_door.y = (int)draw->texture_door.pos
			% (img->door_texture_height[master->type_door]
			[master->index_door] - 1);
		draw->texture_door.pos += draw->texture_door.step;
		draw->texture_door.color = get_door_color(master,
				&draw->texture_door, img);
		if ((draw->texture_door.color & 0xFF000000) == 0)
			my_mlx_pixel_put(img, pos->x, pos->y, draw->texture_door.color);
		pos->y++;
	}
}

void	draw_door(t_intvector *pos, t_data *img, t_master *master)
{
	int			iter;
	t_list		*last;
	t_draw_door	draw;

	if (master->render.is_door)
	{
		iter = 0;
		last = ft_lstlast(master->data_root_door);
		master->data_door = master->data_root_door;
		while (master->data_door != NULL)
		{
			master->type_door = 0;
			master->index_door = 0;
			if (last == master->data_door)
				master->index_door = get_image_index_by_character_type(master);
			draw_door_texture_in_draw_door(pos, img, master, &draw);
			master->data_door = master->data_door->next;
			iter++;
		}
	}
	if (master->data_root_door != NULL)
		ft_lstclear(&master->data_root_door, free_door_data);
	master->data_door = NULL;
	master->data_root_door = NULL;
}
