/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_door_texture_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:29:02 by nmatondo          #+#    #+#             */
/*   Updated: 2025/05/05 16:11:19 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	get_image_quantity_by_door_type(int index)
{
	if (index == 0)
		return (12);
	if (index == 1)
		return (10);
	return (8);
}

void	free_all_loaded_door_images(void *mlx, t_data *img)
{
	int	l;
	int	c;
	int	len;

	l = 0;
	while (l < 3)
	{
		c = 0;
		len = get_image_quantity_by_door_type(l);
		while (c < len)
		{
			if (img->door_texture[l][c])
				mlx_destroy_image(mlx, img->door_texture[l][c]);
			c++;
		}
		l++;
	}
	free_textures(mlx, img);
	free_player_texture(mlx, img);
}

int	load_door_texture_util(void *mlx, t_data *img, int l, int c)
{
	char	*msg;

	img->door_texture[l][c] = mlx_xpm_file_to_image(mlx,
			img->door_texture_paths[l][c],
			&img->door_texture_width[l][c],
			&img->door_texture_height[l][c]);
	if (!img->door_texture[l][c])
	{
		msg = ft_strjoin("image not found ", img->door_texture_paths[l][c]);
		free_all_loaded_door_images(mlx, img);
		return (printerror(msg), free(msg), 1);
	}
	img->door_texture_addr[l][c] = mlx_get_data_addr(img->door_texture[l][c],
			&img->door_texture_bits_per_pixel[l][c],
			&img->door_texture_line_length[l][c],
			&img->door_texture_endian[l][c]);
	return (0);
}

// static 
void	set_path_of_door_images(t_data *img)
{
	int	c;

	c = 0;
	while (c < 13)
	{
		img->door_texture_paths[0][c] = grade_de_cela()[c];
		img->door_texture_paths[1][c] = porta_de_madeira()[c];
		img->door_texture_paths[2][c] = porta_de_dilatacao()[c];
		c++;
	}
}

int	load_door_texture(void *mlx, t_data *img)
{
	int	l;
	int	c;
	int	len;

	l = 0;
	set_path_of_door_images(img);
	while (l < 3)
	{
		c = 0;
		len = get_image_quantity_by_door_type(l);
		while (c < len)
		{
			if (load_door_texture_util(mlx, img, l, c))
				return (1);
			loading();
			c++;
		}
		l++;
	}
	return (0);
}
