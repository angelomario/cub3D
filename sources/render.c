/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:32:11 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/27 11:42:27 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void show_map(char **map)
{
	int i;

	i = 0;
	while (map && map[i])
	{
		printf("%s%s%s\n", GREEN, map[i], RESET);
		i++;
	}
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void clear(t_data *data)
{
	int x;
	int y;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			my_mlx_pixel_put(data, x, y, 0);
			y++;
		}
		x++;
	}
}

void renderization(t_minilib *render, t_master *master, t_data *img)
{
	int x;
	double multiple;
	t_vector pixelCam;
	t_intvector step;
	int hitSide;
	t_intvector wallMapPos;

	x = 0;
	clear(img);
	while (x < SCREEN_WIDTH)
	{
		multiple = 2 * ((double)x / SCREEN_WIDTH) - 1;
		pixelCam = (t_vector){render->plane.x * multiple, render->plane.y * multiple};
		render->rayDir = (t_vector){render->dir.x + pixelCam.x, render->dir.y + pixelCam.y};
		render->deltaDist = setDeltaDist(render->rayDir);
		render->mapPos = (t_intvector){(int)floor(render->pos.x), (int)floor(render->pos.y)};
		render->distToSide = set_distToSide(&step, render->rayDir, render, render->mapPos);
		dda(master, render, &hitSide, &step, &wallMapPos);
		setWallHeight(render, hitSide, wallMapPos, step);
		draw(render->wallHeight, hitSide, x, img);
		x++;
	}
}

void draw(int lineHeight, int hitSide, int x, t_data *img)
{
	int y;
	int drawStart;
	int drawEnd;

	drawStart = (SCREEN_HEIGHT / 2) - (lineHeight / 2);
	drawEnd = (SCREEN_HEIGHT / 2) + (lineHeight / 2);
	if (drawStart < 0)
		drawStart = 0;
	if (drawEnd > SCREEN_HEIGHT)
		drawEnd = SCREEN_HEIGHT;

	y = drawStart;
	while (y < drawEnd)
	{
		if (hitSide)
			my_mlx_pixel_put(img, x, y, 0xa60000);
		else
			my_mlx_pixel_put(img, x, y, 0x7b0000);
		y++;
	}
}
