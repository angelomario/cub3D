/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_animation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 15:08:27 by nmatondo          #+#    #+#             */
/*   Updated: 2025/05/09 14:00:51 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	set_walking_animation(t_master *master)
{
	if ((master->keyboard.down || master->keyboard.up
			|| master->keyboard.left || master->keyboard.right)
		&& !master->keyboard.mouse_left)
	{
		if (master->dimension.l != 1)
		{
			master->dimension.c = 0;
			master->dimension.l = WALK;
			master->limit_time_animation = 6;
		}
	}
}

static void	set_fire_animation(t_master *master)
{
	if (master->keyboard.mouse_left)
	{
		if (master->dimension.l != 0)
		{
			master->dimension.c = 0;
			master->dimension.l = FIRE;
			play_sound(master->weapon, 50, RESTART);
			master->limit_time_animation = 3;
			if (master->dimension.m == 3)
				master->limit_time_animation = 3;
			if (master->dimension.m == 4)
				master->limit_time_animation = 3;
		}
	}
}

static void	set_stop_animation(t_master *master)
{
	if (!master->keyboard.down && !master->keyboard.up
		&& !master->keyboard.left && !master->keyboard.right
		&& !master->keyboard.mouse_left && !master->keyboard.mouse_right)
	{
		master->dimension.c = 0;
		master->dimension.l = STOP;
		master->limit_time_animation = 10;
	}
}

void	player_animation(t_master *master)
{
	int	len;

	set_walking_animation(master);
	set_fire_animation(master);
	set_stop_animation(master);
	if (master->time_animation >= master->limit_time_animation)
	{
		len = get_image_quantity_by_weapon_type(master->dimension.m);
		if (master->dimension.l == 0 && master->dimension.c == (len - 1))
			master->keyboard.mouse_left = false;
		else
		{
			master->dimension.c = (master->dimension.c + 1) % len;
			master->time_animation = 0;
		}
	}
	master->time_animation++;
}
