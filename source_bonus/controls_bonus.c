/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:43:01 by aquissan          #+#    #+#             */
/*   Updated: 2025/05/05 10:31:07 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	rotate_x(t_master *master)
{
	if (master->keyboard.r_right)
	{
		master->render.dir = rotate_vector(master->render.dir, -SPEED);
		master->render.plane = rotate_vector(master->render.plane, -SPEED);
	}
	if (master->keyboard.r_left)
	{
		master->render.dir = rotate_vector(master->render.dir, SPEED);
		master->render.plane = rotate_vector(master->render.plane, SPEED);
	}
}

void	move_x(t_master *m)
{
	t_vector	dir;
	t_minilib	*rd;

	rd = &m->render;
	if (m->keyboard.right)
	{
		dir = (t_vector){rd->dir.y, -rd->dir.x};
		if (valid_character_pass(m->campus[(int)(rd->pos.x + dir.x * (SPEED
						+ 0.1))][(int)(rd->pos.y)], m))
			rd->pos.x += dir.x * SPEED;
		if (valid_character_pass(m->campus[(int)(rd->pos.x)][(int)(rd->pos.y
			+ dir.y * (SPEED + 0.1))], m))
			rd->pos.y += dir.y * SPEED;
	}
	if (m->keyboard.left)
	{
		dir = (t_vector){-rd->dir.y, rd->dir.x};
		if (valid_character_pass(m->campus[(int)(rd->pos.x + dir.x * (SPEED
						+ 0.1))][(int)(rd->pos.y)], m))
			rd->pos.x += dir.x * SPEED;
		if (valid_character_pass(m->campus[(int)(rd->pos.x)][(int)(rd->pos.y
			+ dir.y * (SPEED + 0.1))], m))
			rd->pos.y += dir.y * SPEED;
	}
}

void	move_y(t_master *m)
{
	t_vector	dir;
	t_minilib	*rd;

	rd = &m->render;
	if (m->keyboard.up)
	{
		dir = (t_vector){rd->dir.x, rd->dir.y};
		if (valid_character_pass(m->campus[(int)(rd->pos.x + dir.x * (SPEED
						+ 0.1))][(int)(rd->pos.y)], m))
			rd->pos.x += dir.x * SPEED;
		if (valid_character_pass(m->campus[(int)(rd->pos.x)][(int)(rd->pos.y
			+ dir.y * (SPEED + 0.1))], m))
			rd->pos.y += dir.y * SPEED;
	}
	if (m->keyboard.down)
	{
		dir = (t_vector){-rd->dir.x, -rd->dir.y};
		if (valid_character_pass(m->campus[(int)(rd->pos.x + dir.x * (SPEED
						+ 0.1))][(int)(rd->pos.y)], m))
			rd->pos.x += dir.x * SPEED;
		if (valid_character_pass(m->campus[(int)(rd->pos.x)][(int)(rd->pos.y
			+ dir.y * (SPEED + 0.1))], m))
			rd->pos.y += dir.y * SPEED;
	}
}

int	rotate_y(t_master *master)
{
	if (master->keyboard.r_up)
		master->view_high += SPEED * ROTATE_SPEED;
	if (master->keyboard.r_down)
		master->view_high -= SPEED * ROTATE_SPEED;
	if (master->view_high > SCREEN_HEIGHT / 3)
		master->view_high = SCREEN_HEIGHT / 3;
	if (master->view_high < -SCREEN_HEIGHT / 3)
		master->view_high = -SCREEN_HEIGHT / 3;
	return (0);
}

int	controls(void *vars)
{
	t_master	*master;

	master = (t_master *)vars;
	master->render.door_object_touched = '\0';
	master->rotate_angle++;
	if (master->game_started)
	{
		player_animation(master);
		move_y(master);
		move_x(master);
		rotate_x(master);
		rotate_y(master);
		renderization(&master->render, master, &master->img);
		animation_open_the_door(master);
		animation_close_the_door(master);
		draw_small_map(master);
		draw_player(master);
		draw_crosshair(master);
		mlx_put_image_to_window(master->render.mlx, master->render.win,
			master->img.img, 0, 0);
	}
	else
		preload(master);
	return (0);
}
