/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:29:02 by nmatondo          #+#    #+#             */
/*   Updated: 2025/04/28 11:39:42 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	init_texture_player(t_texture_player *texture_player)
{
	texture_player->scale = 0.0f;
	texture_player->color = 0;
	texture_player->orig_width = 0;
	texture_player->orig_height = 0;
	texture_player->new_width = 0;
	texture_player->new_height = 0;
	texture_player->start_x = 0;
	texture_player->start_y = 0;
	texture_player->src_x = 0;
	texture_player->src_y = 0;
}

static void	player_texture_configuration(t_texture_player *texture_player,
	t_master *master)
{
	if (master->dimension.m == 0)
		shotgun_texture_set(texture_player, master);
	else if (master->dimension.m == 1)
		lupara_texture_setting(texture_player, master);
	else if (master->dimension.m == 2)
		mgun_texture_setting(texture_player, master);
	else if (master->dimension.m == 3)
		shotgun_dub_texture_set(texture_player, master);
	else if (master->dimension.m == 4)
		pistola_texture_setting(texture_player, master);
}

static void	draw_player_util(int x, int y, t_master *master,
	t_texture_player	*texture_player)
{
	texture_player->color = *(int *)(master->img.player_texture_addr
		[master->dimension.m][master->dimension.l][master->dimension.c]
			+ (texture_player->src_y * master->img.player_texture_line_length
			[master->dimension.m][master->dimension.l][master->dimension.c]
				+ texture_player->src_x
				* (master->img.player_texture_bits_per_pixel
				[master->dimension.m]
				[master->dimension.l][master->dimension.c] / 8)));
	if ((texture_player->color & 0xFF000000) == 0)
		my_mlx_pixel_put(&master->img, texture_player->start_x + x,
			texture_player->start_y + y, texture_player->color);
}

void	draw_player(t_master *master)
{
	int					y;
	int					x;
	t_texture_player	texture_player;

	y = 0;
	init_texture_player(&texture_player);
	player_texture_configuration(&texture_player, master);
	while (y < texture_player.new_height)
	{
		x = 0;
		while (x < texture_player.new_width)
		{
			texture_player.src_x = (int)((float)x / texture_player.scale);
			texture_player.src_y = (int)((float)y / texture_player.scale);
			if (texture_player.src_x >= 0
				&& texture_player.src_x < texture_player.orig_width
				&& texture_player.src_y >= 0
				&& texture_player.src_y < texture_player.orig_height)
				draw_player_util(x, y, master, &texture_player);
			x++;
		}
		y++;
	}
}
