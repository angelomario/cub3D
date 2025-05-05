/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_player_texture_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:29:02 by nmatondo          #+#    #+#             */
/*   Updated: 2025/05/05 16:10:57 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	free_all_loaded_player_images(void *mlx, t_data *img,
	t_3d dim, char *path)
{
	while (dim.m >= 0)
	{
		if (dim.l < 0)
			dim.l = get_image_quantity_by_weapon_type(dim.m);
		while (dim.l >= 0)
		{
			if (dim.c < 0)
				dim.c = 12;
			while (dim.c >= 0)
			{
				if (ft_strcmp(path, img->player_texture_paths[dim.m][dim.l]
					[dim.c]) != 0 && ft_strlen(path) != ft_strlen(
						img->player_texture_paths[dim.m][dim.l][dim.c]))
					mlx_destroy_image(mlx,
						img->player_texture[dim.m][dim.l][dim.c]);
				dim.c--;
			}
			dim.l--;
		}
		dim.m--;
	}
	free_textures(mlx, img);
}

int	load_player_texture_util(void *mlx, t_data *img, t_3d dim)
{
	char	*path;
	char	*msg;

	path = ft_strjoin("textures/player/",
			img->player_texture_paths[dim.m][dim.l][dim.c]);
	img->player_texture[dim.m][dim.l][dim.c] = mlx_xpm_file_to_image(mlx, path,
			&img->player_texture_width[dim.m][dim.l][dim.c],
			&img->player_texture_height[dim.m][dim.l][dim.c]);
	if (!img->player_texture[dim.m][dim.l][dim.c])
	{
		free_all_loaded_player_images(mlx, img, dim,
			img->player_texture_paths[dim.m][dim.l][dim.c]);
		msg = ft_strjoin("image not found", path);
		return (printerror(msg), free(msg), free(path), 1);
	}
	img->player_texture_addr[dim.m][dim.l][dim.c] = mlx_get_data_addr(
			img->player_texture[dim.m][dim.l][dim.c],
			&img->player_texture_bits_per_pixel[dim.m][dim.l][dim.c],
			&img->player_texture_line_length[dim.m][dim.l][dim.c],
			&img->player_texture_endian[dim.m][dim.l][dim.c]);
	return (free(path), 0);
}

static t_texture_paths	*path_player_images(void)
{
	int						l;
	int						c;
	static t_texture_paths	paths;

	l = 0;
	while (l < 3)
	{
		c = 0;
		while (c < 14)
		{
			paths[0][l][c] = ((char *(*)[3][14])escopeta())[0][l][c];
			paths[1][l][c] = ((char *(*)[3][14])lupara())[0][l][c];
			paths[2][l][c] = ((char *(*)[3][14])mgun())[0][l][c];
			paths[3][l][c] = ((char *(*)[3][14])escopeta_dupla())[0][l][c];
			paths[4][l][c] = ((char *(*)[3][14])pistola())[0][l][c];
			c++;
		}
		l++;
	}
	return (&paths);
}

static void	set_path_of_player_images(t_data *img)
{
	t_3d			dim;
	t_texture_paths	*player_texture_paths;

	dim.m = 0;
	player_texture_paths = path_player_images();
	while (dim.m < WEAPON_TYPES)
	{
		dim.l = 0;
		while (dim.l < ACTION_TYPES)
		{
			dim.c = 0;
			while (dim.c < IMAGE_COUNT)
			{
				img->player_texture_paths[dim.m][dim.l]
				[dim.c] = (*player_texture_paths)[dim.m][dim.l][dim.c];
				dim.c++;
			}
			dim.l++;
		}
		dim.m++;
	}
}

int	load_player_texture(void *mlx, t_data *img)
{
	int		len;
	t_3d	dim;

	dim.m = 0;
	set_path_of_player_images(img);
	while (dim.m < 5)
	{
		dim.l = 0;
		len = get_image_quantity_by_weapon_type(dim.m);
		while (dim.l < 3)
		{
			dim.c = 0;
			while (dim.c < len)
			{
				if (load_player_texture_util(mlx, img, dim))
					return (1);
				loading();
				dim.c++;
			}
			dim.l++;
		}
		dim.m++;
	}
	return (0);
}
