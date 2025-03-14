/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeze.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:20:22 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/14 12:02:02 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

void	free_textures(t_master *master)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(master->render.mlx, master->img.textures[i]);
		i++;
	}
}
