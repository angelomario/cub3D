/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preload.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:03:40 by aquissan          #+#    #+#             */
/*   Updated: 2025/05/08 15:32:16 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static int	g_pre;

void	preload_pixel_put(t_preload *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	set_step(int pre, int limit)
{
	static int	index_texture;

	if (pre > 100 && pre < 200)
	{
		if ((pre % 100) == (1 * (index_texture + 1)))
			index_texture++;
		if (index_texture >= 7)
			index_texture--;
	}
	if (pre > 200)
	{
		if ((pre % 100) == (8 * (index_texture + 1)))
			index_texture++;
		if (index_texture >= limit)
			index_texture--;
	}
	return (index_texture);
}

int	put_logo(t_master *master, int x, int y)
{
	t_intvector	tex;
	int			color;
	t_image		img;

	g_pre++;
	img = master->preload.logo[set_step(g_pre, 13)];
	tex = (t_intvector){0, 0};
	while (tex.x < img.width && tex.x < SCREEN_WIDTH)
	{
		tex.y = 0;
		while (tex.y < img.height && tex.y < SCREEN_HEIGHT)
		{
			color = *(unsigned int *)(img.addr + (tex.y * img.line_length
						+ tex.x * (img.bits_per_pixel / 8)));
			if (!((color & 0x00FFFFFF) == 0x000000))
				preload_pixel_put(&master->preload, x + tex.x, y + tex.y,
					color);
			tex.y++;
		}
		tex.x++;
	}
	return (0);
}

int	preload(t_master *master)
{
	t_intvector	tex;
	int			color;
	int			x;
	int			y;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		y = 0;
		while (y < SCREEN_HEIGHT)
		{
			tex.x = (x * master->preload.background.width) / SCREEN_WIDTH;
			tex.y = (y * master->preload.background.height) / SCREEN_HEIGHT;
			color = *(unsigned int *)(master->preload.background.addr + (tex.y
						* master->preload.background.line_length + tex.x
						* (master->preload.background.bits_per_pixel / 8)));
			preload_pixel_put(&master->preload, x, y++, color);
		}
	}
	put_logo(master, (SCREEN_WIDTH / 2) - (master->preload.logo[0].width / 2),
		(SCREEN_HEIGHT / 2) - (master->preload.logo[0].height * 1.8));
	return (mlx_put_image_to_window(master->render.mlx, master->render.win,
			master->preload.img, 0, 0), 0);
	(void)master;
	return (0);
}
