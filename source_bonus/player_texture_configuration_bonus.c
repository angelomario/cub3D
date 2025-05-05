/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_texture_configuration_bonus.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 15:45:25 by nmatondo          #+#    #+#             */
/*   Updated: 2025/04/28 11:40:10 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	shotgun_texture_set(t_texture_player *texture_player,
	t_master *master)
{
	texture_player->orig_width = master->img.player_texture_width
	[master->dimension.m][master->dimension.l][master->dimension.c];
	texture_player->orig_height = master->img.player_texture_height
	[master->dimension.m][master->dimension.l][master->dimension.c];
	texture_player->scale = 3.7f;
	texture_player->new_width = texture_player->orig_width
		* texture_player->scale;
	texture_player->new_height = texture_player->orig_height
		* texture_player->scale;
	texture_player->start_x = 370;
	texture_player->start_y = -113;
}

void	lupara_texture_setting(t_texture_player *texture_player,
	t_master *master)
{
	texture_player->orig_width = master->img.player_texture_width
	[master->dimension.m][master->dimension.l][master->dimension.c];
	texture_player->orig_height = master->img.player_texture_height
	[master->dimension.m][master->dimension.l][master->dimension.c];
	texture_player->scale = 2.5f;
	texture_player->new_width = texture_player->orig_width
		* texture_player->scale;
	texture_player->new_height = texture_player->orig_height
		* texture_player->scale;
	texture_player->start_x = 530;
	texture_player->start_y = 182;
}

void	mgun_texture_setting(t_texture_player *texture_player,
	t_master *master)
{
	texture_player->orig_width = master->img.player_texture_width
	[master->dimension.m][master->dimension.l][master->dimension.c];
	texture_player->orig_height = master->img.player_texture_height
	[master->dimension.m][master->dimension.l][master->dimension.c];
	texture_player->scale = 3.3f;
	texture_player->new_width = texture_player->orig_width
		* texture_player->scale;
	texture_player->new_height = texture_player->orig_height
		* texture_player->scale;
	texture_player->start_x = 80;
	texture_player->start_y = 140;
}

void	shotgun_dub_texture_set(t_texture_player *texture_player,
	t_master *master)
{
	texture_player->orig_width = master->img.player_texture_width
	[master->dimension.m][master->dimension.l][master->dimension.c];
	texture_player->orig_height = master->img.player_texture_height
	[master->dimension.m][master->dimension.l][master->dimension.c];
	texture_player->scale = 3.3f;
	texture_player->new_width = texture_player->orig_width
		* texture_player->scale;
	texture_player->new_height = texture_player->orig_height
		* texture_player->scale;
	texture_player->start_x = 560;
	texture_player->start_y = -16;
}

void	pistola_texture_setting(t_texture_player *texture_player,
	t_master *master)
{
	texture_player->orig_width = master->img.player_texture_width
	[master->dimension.m][master->dimension.l][master->dimension.c];
	texture_player->orig_height = master->img.player_texture_height
	[master->dimension.m][master->dimension.l][master->dimension.c];
	texture_player->scale = 4.5f;
	texture_player->new_width = texture_player->orig_width
		* texture_player->scale;
	texture_player->new_height = texture_player->orig_height
		* texture_player->scale;
	texture_player->start_x = 410;
	texture_player->start_y = -300;
}
