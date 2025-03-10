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
	int			hitSide;
	double		multiple;
	t_vector	pixelCam;
	t_intvector	pos;
	t_intvector	step;
	t_intvector	wallMapPos;

	pos.x = 0;
	clear(img);
	while (pos.x < SCREEN_WIDTH)
	{
		multiple = 2 * ((double)pos.x / SCREEN_WIDTH) - 1;
		pixelCam = (t_vector){render->plane.x * multiple, render->plane.y * multiple};
		render->rayDir = (t_vector){render->dir.x + pixelCam.x, render->dir.y + pixelCam.y};
		render->deltaDist = setDeltaDist(render->rayDir);
		render->mapPos = (t_intvector){(int)floor(render->pos.x), (int)floor(render->pos.y)};
		render->distToSide = set_distToSide(&step, render->rayDir, render, render->mapPos);
		dda(master, render, &hitSide, &step, &wallMapPos);
		setWallHeight(render, hitSide, wallMapPos, step);
		draw_texture(hitSide, &pos, img, master);
		pos.x++;
	}
}




void	draw_ceiling(int drawStart, t_intvector *pos, t_data *img, t_master *master)
{
	int i;

	i = 0;
	while (i < drawStart)
	{
		my_mlx_pixel_put(img, pos->x, i++, master->C);
	}
}

void	draw_floor(t_intvector *pos, t_data *img, t_master *master)
{
	while (pos->y < SCREEN_HEIGHT)
		my_mlx_pixel_put(img, pos->x, pos->y++, master->F);
}

int	get_x_coordinate_texture(int index_img, int hitSide, t_master *master, t_data *img)
{
	int texX;
	double wallX;

	if (hitSide == 0)
		wallX = master->render.pos.y + master->render.perpendicularDist * master->render.rayDir.y;
	else
		wallX = master->render.pos.x + master->render.perpendicularDist * master->render.rayDir.x;
	wallX -= floor(wallX);

	// Calcular a coordenada x da textura
	texX = (int)(wallX * (double)img->tex_width[index_img]);
	if ((hitSide == 0 && master->render.rayDir.x > 0)
		|| (hitSide == 1 && master->render.rayDir.y < 0))
		texX = img->tex_width[index_img] - texX - 1;
	return (texX);
}

int	get_draw_start_position(int lineHeight)
{
	int drawStart;

	drawStart = (SCREEN_HEIGHT / 2) - (lineHeight / 2);
	if (drawStart < 0)
		drawStart = 0;
	return (drawStart);
}

int	get_draw_end_position(int lineHeight)
{
	int drawEnd;

	drawEnd = (SCREEN_HEIGHT / 2) + (lineHeight / 2);
	if (drawEnd > SCREEN_HEIGHT)
		drawEnd = SCREEN_HEIGHT;
	return (drawEnd);
}

int get_texture_index(int hitSide, t_vector rayDir)
{
	if (hitSide == 1)
	{
		if (rayDir.y > 0)
			return 2;
		else
			return 3;
	}
	else
	{
		if (rayDir.x > 0)
			return 1;
		else
			return 0;
	}
}

static unsigned int darken_color(unsigned int color, int percentage)
{
	int r;
	int g;
	int b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;

	r = (int)(r * (100 - percentage) / 100);
	g = (int)(g * (100 - percentage) / 100);
	b = (int)(b * (100 - percentage) / 100);

	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

unsigned int get_color(int hitSide, t_texture *texture, t_data *img)
{
	unsigned int	color;

	color = *(unsigned int *)(img->tex_addr[texture->index] + (texture->y
		* img->tex_line_length[texture->index] + texture->x
		* (img->tex_bits_per_pixel[texture->index] / 8)));
	if (hitSide == 1)
		color = darken_color(color, 30);
	return (color);
}

void	draw_texture(int hitSide, t_intvector *pos, t_data *img, t_master *master)
{
	int			start;
	int			end;
	t_texture	texture;

	start = get_draw_start_position(master->render.wallHeight);
	end = get_draw_end_position(master->render.wallHeight);
	draw_ceiling(start, pos, img, master);
	texture.index = get_texture_index(hitSide, master->render.rayDir);
	texture.x = get_x_coordinate_texture(texture.index, hitSide, master, img);
	texture.step = 1.0 * img->tex_height[texture.index] / master->render.wallHeight;
	texture.pos = (start - SCREEN_HEIGHT / 2 + master->render.wallHeight / 2) * texture.step;
	pos->y = start;
	while (pos->y < end)
	{
		texture.y = (int)texture.pos % (img->tex_height[texture.index] - 1);
		texture.pos += texture.step;
		texture.color = get_color(hitSide, &texture, img);
		my_mlx_pixel_put(img, pos->x, pos->y++, texture.color);
	}
	draw_floor(pos, img, master);
}
