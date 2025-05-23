/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:43:01 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/18 08:28:03 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	rotate(t_master *master)
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

void	move_x(t_master *master)
{
	t_vector	dir;
	t_minilib	*rd;

	rd = &master->render;
	if (master->keyboard.right)
	{
		dir = (t_vector){rd->dir.y, -rd->dir.x};
		if (master->campus[(int)(rd->pos.x + dir.x * (SPEED
					+ 0.1))][(int)(rd->pos.y)] != '1')
			rd->pos.x += dir.x * SPEED;
		if (master->campus[(int)(rd->pos.x)][(int)(rd->pos.y + dir.y * (SPEED
					+ 0.1))] != '1')
			rd->pos.y += dir.y * SPEED;
	}
	if (master->keyboard.left)
	{
		dir = (t_vector){-rd->dir.y, rd->dir.x};
		if (master->campus[(int)(rd->pos.x + dir.x * (SPEED
					+ 0.1))][(int)(rd->pos.y)] != '1')
			rd->pos.x += dir.x * SPEED;
		if (master->campus[(int)(rd->pos.x)][(int)(rd->pos.y + dir.y * (SPEED
					+ 0.1))] != '1')
			rd->pos.y += dir.y * SPEED;
	}
}

void	move_y(t_master *master)
{
	t_vector	dir;
	t_minilib	*rd;

	rd = &master->render;
	if (master->keyboard.up)
	{
		dir = (t_vector){rd->dir.x, rd->dir.y};
		if (master->campus[(int)(rd->pos.x + dir.x * (SPEED
					+ 0.1))][(int)(rd->pos.y)] != '1')
			rd->pos.x += dir.x * SPEED;
		if (master->campus[(int)(rd->pos.x)][(int)(rd->pos.y + dir.y * (SPEED
					+ 0.1))] != '1')
			rd->pos.y += dir.y * SPEED;
	}
	if (master->keyboard.down)
	{
		dir = (t_vector){-rd->dir.x, -rd->dir.y};
		if (master->campus[(int)(rd->pos.x + dir.x * (SPEED
					+ 0.1))][(int)(rd->pos.y)] != '1')
			rd->pos.x += dir.x * SPEED;
		if (master->campus[(int)(rd->pos.x)][(int)(rd->pos.y + dir.y * (SPEED
					+ 0.1))] != '1')
			rd->pos.y += dir.y * SPEED;
	}
}

int	controls(void *vars)
{
	t_master	*master;

	master = (t_master *)vars;
	rotate(master);
	move_y(master);
	move_x(master);
	renderization(&master->render, master, &master->img);
	mlx_put_image_to_window(master->render.mlx, master->render.win,
		master->img.img, 0, 0);
	return (0);
}

int	wait_hooks(t_master *master)
{
	mlx_hook(master->render.win, 2, 1L << 0, key_hook, master);
	mlx_hook(master->render.win, 3, 1L << 1, key_release, master);
	mlx_hook(master->render.win, 17, 1L << 1, key_exit, master);
	return (0);
}
