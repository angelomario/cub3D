/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_exit_bounus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 09:50:57 by nmatondo          #+#    #+#             */
/*   Updated: 2025/05/08 12:44:36 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	key_exit(t_master *master)
{
	free_root_focused_close_door(master);
	free_preload(&master->preload, master->render.mlx);
	free_door_texture(master->render.mlx, &master->img);
	free_textures(master->render.mlx, &master->img);
	free_player_texture(master->render.mlx, &master->img);
	mlx_destroy_image(master->render.mlx, master->img.img);
	mlx_destroy_window(master->render.mlx, master->render.win);
	mlx_destroy_display(master->render.mlx);
	free(master->render.mlx);
	ft_free_master(master);
	exit(0);
	return (0);
}

int	key_exit_2(t_master *master)
{
	free_root_focused_close_door(master);
	free_preload(&master->preload, master->render.mlx);
	free_door_texture(master->render.mlx, &master->img);
	free_textures(master->render.mlx, &master->img);
	free_player_texture(master->render.mlx, &master->img);
	mlx_destroy_image(master->render.mlx, master->img.img);
	mlx_destroy_window(master->render.mlx, master->render.win);
	mlx_destroy_display(master->render.mlx);
	free(master->render.mlx);
	ft_free_master(master);
	exit(0);
	return (0);
}
