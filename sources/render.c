/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:32:11 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/14 11:59:46 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clear(t_data *data)
{
	int	x;
	int	y;

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

void	renderization(t_minilib *render, t_master *master, t_data *img)
{
	int			hitside;
	double		multiple;
	t_vector	pixelcam;
	t_intvector	pos;
	t_intvector	step;

	pos.x = -1;
	clear(img);
	while (++pos.x < SCREEN_WIDTH)
	{
		multiple = 2 * ((double)pos.x / SCREEN_WIDTH) - 1;
		pixelcam = (t_vector){render->plane.x * multiple, render->plane.y
			* multiple};
		render->raydir = (t_vector){render->dir.x + pixelcam.x, render->dir.y
			+ pixelcam.y};
		render->deltadist = setdeltadist(render->raydir);
		render->mappos = (t_intvector){(int)floor(render->pos.x),
			(int)floor(render->pos.y)};
		render->disttoside = set_disttoside(&step, render->raydir, render,
				render->mappos);
		dda(master, &hitside, &step, &master->wallmappos);
		setwallheight(render, hitside, master->wallmappos, step);
		draw_texture(hitside, &pos, img, master);
	}
}

int	get_x_coordinate_texture(int index_img, int hitSide, t_master *master,
		t_data *img)
{
	int		texx;
	double	wallx;

	if (hitSide == 0)
		wallx = master->render.pos.y + master->render.perpendiculardist
			* master->render.raydir.y;
	else
		wallx = master->render.pos.x + master->render.perpendiculardist
			* master->render.raydir.x;
	wallx -= floor(wallx);
	texx = (int)(wallx * (double)img->tex_width[index_img]);
	if ((hitSide == 0 && master->render.raydir.x > 0) || (hitSide == 1
			&& master->render.raydir.y < 0))
		texx = img->tex_width[index_img] - texx - 1;
	return (texx);
}
