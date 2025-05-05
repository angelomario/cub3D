/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:51:14 by aquissan          #+#    #+#             */
/*   Updated: 2025/04/28 11:06:45 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	draw_texture(t_intvector *pos, t_data *img, t_master *master)
{
	int			start;
	int			end;
	t_texture	texture;

	start = get_draw_start_position(master->render.wallheight, master);
	end = get_draw_end_position(master->render.wallheight, master);
	draw_skybox(start, pos, img, master);
	texture.index = get_texture_index(master->wall_hitside,
			master->render.raydir);
	texture.x = get_x_coordinate_texture(texture.index, master->wall_hitside,
			master, img);
	texture.step = 1.0 * img->tex_height[texture.index]
		/ master->render.wallheight;
	texture.pos = ((start - master->view_high) - SCREEN_HEIGHT / 2
			+ master->render.wallheight / 2) * texture.step;
	pos->y = start;
	while (pos->y < end)
	{
		texture.y = (int)texture.pos % (img->tex_height[texture.index] - 1);
		texture.pos += texture.step;
		texture.color = get_color(master->wall_hitside, &texture, img);
		my_mlx_pixel_put(img, pos->x, pos->y++, texture.color);
	}
	draw_floor(pos, img, master);
}

void	draw_ceiling(int drawStart, t_intvector *pos, t_data *img,
		t_master *master)
{
	int	i;

	i = 0;
	while (i < drawStart)
	{
		my_mlx_pixel_put(img, pos->x, i++, master->c);
	}
}

void	show_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		printf("%s%s%s\n", GREEN, map[i], RESET);
		i++;
	}
}
