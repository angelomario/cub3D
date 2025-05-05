/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_small_map_area_value_bouns.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          #+#  +:+        +#+       */
/*                                                +#+#+#+#+#+	+#+           */
/*   Created: 2025-03-20 12:10:04 by nmatondo          #+#    #+#             */
/*   Updated: 2025-03-20 12:10:04 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	get_height_player_line(t_master *master)
{
	int	i;

	i = 0;
	while (master->campus[i])
		i++;
	return (i);
}

int	get_width_player_line(t_master *master)
{
	int	i;

	i = 0;
	while (master->campus[
			(int)master->render.pos.x][i])
		i++;
	return (i);
}

void	set_area_value(t_master *master, t_size *size, t_area *area,
		t_area *extra)
{
	area->ini_x = (int)master->render.pos.x - 5;
	if (area->ini_x < 0)
	{
		extra->ini_x = area->ini_x * -1;
		area->ini_x = 0;
	}
	area->end_x = (int)master->render.pos.x + 5;
	if (area->end_x > size->height)
	{
		extra->end_x = area->end_x - size->height;
		area->end_x = size->height;
	}
	area->ini_y = (int)master->render.pos.y - 5;
	if (area->ini_y < 0)
	{
		extra->ini_y = area->ini_y * -1;
		area->ini_y = 0;
	}
	area->end_y = (int)master->render.pos.y + 5;
	if (area->end_y > size->width)
	{
		extra->end_y = area->end_y - size->width;
		area->end_y = size->width;
	}
}

void	adjust_initial_area_values(t_master *master, t_area *area,
		t_area *extra)
{
	int	i;

	if (extra->ini_x > 0)
	{
		i = 0;
		while (extra->ini_x && master->campus[area->end_x + i++])
			extra->ini_x--;
		area->end_x += i;
	}
	if (extra->ini_y > 0)
	{
		i = 0;
		while (extra->ini_y && master->campus[area->end_y + i++])
			extra->ini_y--;
		area->end_y += i;
	}
}

void	adjust_final_area_values(t_master *master, t_area *area, t_area *extra)
{
	int	i;

	if (extra->end_x > 0)
	{
		i = 0;
		while (extra->end_x && master->campus[area->ini_x - i++])
			extra->end_x--;
		area->ini_x -= i;
	}
	if (extra->end_y > 0)
	{
		i = 0;
		while (extra->end_y && master->campus[area->ini_y - i++])
			extra->end_y--;
		area->ini_y -= i;
	}
}
