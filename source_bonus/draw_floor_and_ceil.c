/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_and_ceil.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:05:08 by aquissan          #+#    #+#             */
/*   Updated: 2025/05/08 12:02:36 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	get_peripheral_color(t_data *img, t_intvector tex, char peripheral,
		t_master *master)
{
	char	*pixel;
	int		color;

	(void)master;
	if (peripheral != 'f' && peripheral != 'c')
		return (0xFF000000);
	if (peripheral == 'f')
	{
		pixel = img->floor_texture_addr + tex.y * img->floor_texture_line_length
			+ tex.x * (img->floor_texture_bits_per_pixel / 8);
		color = *(unsigned int *)pixel;
		color += master->f;
	}
	return (color);
}

void	calc_pixel(t_floor_var *var, t_intvector *pos, t_master *master,
		t_data *img)
{
	var->row_distance = (0.5 * SCREEN_HEIGHT) / var->p;
	var->camera_factor = (double)pos->x / SCREEN_WIDTH;
	var->floor.x = master->render.pos.x + var->row_distance * (var->left_ray.x
			+ var->camera_factor * (var->right_ray.x - var->left_ray.x));
	var->floor.y = master->render.pos.y + var->row_distance * (var->left_ray.y
			+ var->camera_factor * (var->right_ray.y - var->left_ray.y));
	var->tex.x = (int)(var->floor.x * img->floor_texture_width)
		% img->floor_texture_width;
	if (var->tex.x < 0)
		var->tex.x += img->floor_texture_width;
	var->tex.y = (int)(var->floor.y * img->floor_texture_height)
		% img->floor_texture_height;
	if (var->tex.y < 0)
		var->tex.y += img->floor_texture_height;
}

void	draw_floor(t_intvector *pos, t_data *img, t_master *master)
{
	int			y;
	t_floor_var	var;

	var.left_ray.x = master->render.dir.x - master->render.plane.x;
	var.left_ray.y = master->render.dir.y - master->render.plane.y;
	var.right_ray.x = master->render.dir.x + master->render.plane.x;
	var.right_ray.y = master->render.dir.y + master->render.plane.y;
	y = pos->y;
	while (y < SCREEN_HEIGHT)
	{
		var.p = y - SCREEN_HEIGHT / 2 - master->view_high;
		if (var.p <= 0)
		{
			y++;
			continue ;
		}
		calc_pixel(&var, pos, master, img);
		my_mlx_pixel_put(img, pos->x, y, get_peripheral_color(img, var.tex, 'f',
				master));
		y++;
	}
}

int	get_sky_pic_color(t_ceil_var ceil, t_data *img)
{
	ceil.pixel = img->ceil_texture_addr + ceil.sky.y
		* img->ceil_texture_line_length + ceil.sky.x
		* (img->ceil_texture_bits_per_pixel / 8);
	ceil.color = *(unsigned int *)ceil.pixel;
	return (ceil.color);
}

void	draw_skybox(int drawStart, t_intvector *pos, t_data *img,
		t_master *master)
{
	int			y;
	t_ceil_var	ceil;

	y = 0;
	ceil.angle = (atan2(master->render.dir.x, master->render.dir.y));
	ceil.angle -= (PI) / 2;
	ceil.angle += ((double)pos->x / SCREEN_WIDTH) * (PI);
	while (y < drawStart)
	{
		if (ceil.angle < 0)
			ceil.angle += 2 * PI;
		if (ceil.angle >= 2 * PI)
			ceil.angle -= 2 * PI;
		ceil.sky.x = (int)((ceil.angle / (2 * PI)) * img->ceil_texture_width);
		ceil.v_offset = (double)(y - master->view_high) / (SCREEN_HEIGHT / 2);
		ceil.sky.y = (int)((ceil.v_offset) * img->ceil_texture_height);
		if (ceil.sky.y < 0)
			ceil.sky.y = 0;
		if (ceil.sky.y >= img->ceil_texture_height)
			ceil.sky.y = img->ceil_texture_height - 1;
		ceil.color = get_sky_pic_color(ceil, img);
		my_mlx_pixel_put(img, pos->x, y, ceil.color + master->c);
		y++;
	}
}
