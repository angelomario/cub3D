/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:43:01 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/27 18:10:13 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void rotate(t_master *master)
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

void move_x(t_master *master)
{
	t_vector dir;

	if (master->keyboard.right)
	{
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
}

void move_y(t_master *master)
{
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
}

int controls(void *vars)
{
    t_master *master;

    master = (t_master *)vars;
    rotate(master);
    move_y(master);
    move_x(master);
    renderization(&master->render, master, &master->img);
    mlx_put_image_to_window(master->render.mlx, master->render.win, master->img.img, 0, 0);
    return (0);
}