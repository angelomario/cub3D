/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:43:01 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/27 17:52:26 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void rotate(t_master *master)
{
<<<<<<< HEAD
	if (master->keyboard.r_right)
	{
		master->render.dir = rotate_vector(master->render.dir, -ROTATE_SPEED);
		master->render.plane = rotate_vector(master->render.plane, -ROTATE_SPEED);
	}
	if (master->keyboard.r_left)
	{
		master->render.dir = rotate_vector(master->render.dir, ROTATE_SPEED);
		master->render.plane = rotate_vector(master->render.plane, ROTATE_SPEED);
	}
=======
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
>>>>>>> d1fb106 (done)
}

void move_x(t_master *master)
{
	t_vector dir;

	if (master->keyboard.right)
	{

<<<<<<< HEAD
		dir.y = master->render.dir.y;
		dir.x = -master->render.dir.x;
		if (master->campus[(int)(master->render.pos.x + dir.y * MOVE_SPEED)]
							[(int)(master->render.pos.y)] != '1')
			master->render.pos.x += dir.y * MOVE_SPEED;
		if (master->campus[(int)(master->render.pos.x)]
							[(int)(master->render.pos.y + dir.x * MOVE_SPEED)] != '1')
			master->render.pos.y += dir.x * MOVE_SPEED;
	}
	if (master->keyboard.left)
	{
		dir.y = master->render.dir.y;
		dir.x = -master->render.dir.x;
		if (master->campus[(int)(master->render.pos.x - dir.y * MOVE_SPEED)]
							[(int)(master->render.pos.y)] != '1')
			master->render.pos.x -= dir.y * MOVE_SPEED;
		if (master->campus[(int)(master->render.pos.x)]
							[(int)(master->render.pos.y - dir.x * MOVE_SPEED)] != '1')
			master->render.pos.y -= dir.x * MOVE_SPEED;
	}
=======
        dir.y = master->render.dir.y;
        dir.x = -master->render.dir.x;
        if (master->campus[(int)(master->render.pos.x + dir.y * SPEED)]
                          [(int)(master->render.pos.y)] != '1')
            master->render.pos.x += dir.y * SPEED;
        if (master->campus[(int)(master->render.pos.x)]
                          [(int)(master->render.pos.y + dir.x * SPEED)] != '1')
            master->render.pos.y += dir.x * SPEED;
    }
    if (master->keyboard.left)
    {
        dir.y = master->render.dir.y;
        dir.x = -master->render.dir.x;
        if (master->campus[(int)(master->render.pos.x - dir.y * SPEED)]
                          [(int)(master->render.pos.y)] != '1')
            master->render.pos.x -= dir.y * SPEED;
        if (master->campus[(int)(master->render.pos.x)]
                          [(int)(master->render.pos.y - dir.x * SPEED)] != '1')
            master->render.pos.y -= dir.x * SPEED;
    }
>>>>>>> d1fb106 (done)
}

void move_y(t_master *master)
{
<<<<<<< HEAD
	if (master->keyboard.up)
	{
		if (master->campus[(int)(master->render.pos.x + master->render.dir.x * MOVE_SPEED)]
							[(int)(master->render.pos.y)] != '1')
			master->render.pos.x += master->render.dir.x * MOVE_SPEED;
		if (master->campus[(int)(master->render.pos.x)]
							[(int)(master->render.pos.y + master->render.dir.y * MOVE_SPEED)] != '1')
			master->render.pos.y += master->render.dir.y * MOVE_SPEED;
	}
	if (master->keyboard.down)
	{
		if (master->campus[(int)(master->render.pos.x - master->render.dir.x * MOVE_SPEED)]
							[(int)(master->render.pos.y)] != '1')
			master->render.pos.x -= master->render.dir.x * MOVE_SPEED;
		if (master->campus[(int)(master->render.pos.x)]
							[(int)(master->render.pos.y - master->render.dir.y * MOVE_SPEED)] != '1')
			master->render.pos.y -= master->render.dir.y * MOVE_SPEED;
	}
=======
    if (master->keyboard.up)
    {
        if (master->campus[(int)((master->render.pos.x + master->render.dir.x * SPEED))]
                          [(int)(master->render.pos.y)] != '1')
            master->render.pos.x += master->render.dir.x * SPEED;
        if (master->campus[(int)(master->render.pos.x)]
                          [(int)(master->render.pos.y + master->render.dir.y * SPEED)] != '1')
            master->render.pos.y += master->render.dir.y * SPEED;
    }
    if (master->keyboard.down)
    {
        if (master->campus[(int)(master->render.pos.x - master->render.dir.x * SPEED)]
                          [(int)(master->render.pos.y)] != '1')
            master->render.pos.x -= master->render.dir.x * SPEED;
        if (master->campus[(int)(master->render.pos.x)]
                          [(int)(master->render.pos.y - master->render.dir.y * SPEED)] != '1')
            master->render.pos.y -= master->render.dir.y * SPEED;
    }
>>>>>>> d1fb106 (done)
}

int controls(void *vars)
{
<<<<<<< HEAD
	t_master *master;
	t_keyboard keyboard;

	master = (t_master *)vars;
	keyboard = master->keyboard;
	(void)keyboard;
	rotate(master);
	move_x(master);
	move_y(master);
	renderization(&master->render, master, &master->img);
	mlx_put_image_to_window(master->render.mlx, master->render.win, master->img.img, 0, 0);
	return (0);
=======
    t_master *master;

    master = (t_master *)vars;
    rotate(master);
    move_y(master);
    move_x(master);
    renderization(&master->render, master, &master->img);
    mlx_put_image_to_window(master->render.mlx, master->render.win, master->img.img, 0, 0);
    return (0);
>>>>>>> d1fb106 (done)
}
