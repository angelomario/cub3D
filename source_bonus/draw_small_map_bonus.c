/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_small_map_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:10:04 by nmatondo          #+#    #+#             */
/*   Updated: 2025/05/05 13:17:25 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	draw_map_border(t_master *master, t_area *area)
{
	t_vector	pos;
	t_bresenham	line;

	pos.x = 1 * PIXEL_SIZE;
	pos.y = 1 * PIXEL_SIZE;
	line.y_ini = pos.y - 3;
	line.x_ini = pos.x - 3;
	line.y_end = pos.y - 3;
	line.x_end = (area->end_x - area->ini_x + 2) * PIXEL_SIZE;
	draw_straight_line(master, &line, 3, 0x2471a3);
	line.y_ini = pos.y - 3;
	line.x_ini = pos.x - 3;
	line.y_end = (area->end_y - area->ini_y + 2) * PIXEL_SIZE;
	line.x_end = pos.x - 3;
	draw_straight_line(master, &line, 3, 0x2471a3);
	line.y_ini = pos.y - 3;
	line.x_ini = (area->end_x - area->ini_x + 2) * PIXEL_SIZE;
	line.y_end = (area->end_y - area->ini_y + 2) * PIXEL_SIZE;
	line.x_end = (area->end_x - area->ini_x + 2) * PIXEL_SIZE;
	draw_straight_line(master, &line, 3, 0x2471a3);
	line.y_ini = (area->end_y - area->ini_y + 2) * PIXEL_SIZE;
	line.x_ini = pos.x - 3;
	line.y_end = (area->end_y - area->ini_y + 2) * PIXEL_SIZE;
	line.x_end = (area->end_x - area->ini_x + 2) * PIXEL_SIZE;
	draw_straight_line(master, &line, 3, 0x2471a3);
}

static void	draw_map(t_master *master, t_area *area)
{
	int			i1;
	int			i2;
	t_vector	aux;
	t_vector	pos;

	aux.y = 1;
	i1 = area->ini_x;
	while (i1 <= area->end_x)
	{
		aux.x = 1;
		i2 = area->ini_y;
		while (i2 <= area->end_y)
		{
			pos.x = aux.x * PIXEL_SIZE;
			pos.y = aux.y * PIXEL_SIZE;
			draw_map_util(master, pos, i1, i2);
			i2++;
			aux.x++;
		}
		i1++;
		aux.y++;
	}
}

static void	draw_small_player_util(t_master *master, int x, int y)
{
	t_vector	pos;
	t_bresenham	line;
	int			rest_x;
	int			rest_y;

	rest_x = ((master->render.pos.y - (int)master->render.pos.y) * 10);
	rest_y = ((master->render.pos.x - (int)master->render.pos.x) * 10);
	pos.x = (x * PIXEL_SIZE) + rest_x;
	pos.y = (y * PIXEL_SIZE) + rest_y;
	draw_big_pixel(master, PIXEL_SIZE - 8, pos, 0xFF0000);
	line.x_ini = (x * PIXEL_SIZE) + ((PIXEL_SIZE - 9) / 2) + rest_x;
	line.y_ini = (y * PIXEL_SIZE) + ((PIXEL_SIZE - 9) / 2) + rest_y;
	line.x_end = (x * PIXEL_SIZE) + ((PIXEL_SIZE - 9) / 2) + rest_x
		+ (master->render.dir.y * (PIXEL_SIZE / 2 + 4));
	line.y_end = (y * PIXEL_SIZE) + ((PIXEL_SIZE - 9) / 2) + rest_y
		+ (master->render.dir.x * (PIXEL_SIZE / 2 + 4));
	draw_straight_line(master, &line, PIXEL_SIZE / 10, 0x00ff00);
}

static void	draw_small_player(t_master *master, t_area *area)
{
	int	x;
	int	y;
	int	i1;
	int	i2;

	y = 1;
	i1 = area->ini_x;
	while (i1 <= area->end_x)
	{
		x = 1;
		i2 = area->ini_y;
		while (i2 <= area->end_y)
		{
			if ((int)master->render.pos.x == i1
				&& (int)master->render.pos.y == i2)
				draw_small_player_util(master, x, y);
			i2++;
			x++;
		}
		i1++;
		y++;
	}
}

void	draw_small_map(t_master *master)
{
	t_area	area;
	t_area	extra;
	t_size	size;

	size.height = get_height_player_line(master) - 1;
	size.width = get_width_player_line(master) - 1;
	area = (t_area){0, 0, 0, 0};
	extra = (t_area){0, 0, 0, 0};
	set_area_value(master, &size, &area, &extra);
	adjust_initial_area_values(master, &area, &extra);
	adjust_final_area_values(master, &area, &extra);
	draw_map_border(master, &area);
	draw_map(master, &area);
	draw_small_player(master, &area);
}
