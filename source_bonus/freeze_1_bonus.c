/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeze_1_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:20:22 by aquissan          #+#    #+#             */
/*   Updated: 2025/05/08 15:33:13 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	ft_free_stack(t_map *map)
{
	t_map	*tmp;

	while (map)
	{
		tmp = map;
		map = map->next;
		free(tmp->line);
		free(tmp);
	}
}

void	ft_free_master(t_master *master)
{
	if (master->so)
		free(master->so);
	if (master->we)
		free(master->we);
	if (master->ea)
		free(master->ea);
	if (master->no)
		free(master->no);
	if (master->campus)
		ft_freematriz(master->campus);
	clear_sounds(master->sounds, master->bass_active);
	free(master);
}

int	ft_freematriz(char **mat)
{
	int	i;

	i = -1;
	if (mat != NULL)
	{
		while (mat && mat[++i])
			free(mat[i]);
		free(mat);
	}
	return (i);
}

int	free_textures(void *mlx, t_data *img)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(mlx, img->textures[i]);
		i++;
	}
	mlx_destroy_image(mlx, img->floor_texture);
	mlx_destroy_image(mlx, img->ceil_texture);
	return (0);
}

int	free_player_texture(void *mlx, t_data *img)
{
	int		len;
	t_3d	dim;

	dim.m = 0;
	while (dim.m < 5)
	{
		dim.l = 0;
		len = get_image_quantity_by_weapon_type(dim.m);
		while (dim.l < 3)
		{
			dim.c = 0;
			while (dim.c < len)
			{
				if (img->player_texture[dim.m][dim.l][dim.c])
					mlx_destroy_image(mlx,
						img->player_texture[dim.m][dim.l][dim.c]);
				dim.c++;
			}
			dim.l++;
		}
		dim.m++;
	}
	return (0);
}
