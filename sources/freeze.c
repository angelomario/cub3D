/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeze.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:20:22 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/13 13:46:28 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void ft_free_stack(t_map *map)
{
	t_map *tmp;

	while (map)
	{
		tmp = map;
		map = map->next;
		free(tmp->line);
		free(tmp);
	}
}

void ft_free_master(t_master *master)
{
	if (master->SO)
		free(master->SO);
	if (master->WE)
		free(master->WE);
	if (master->EA)
		free(master->EA);
	if (master->NO)
		free(master->NO);
	if (master->campus)
		ft_freematriz(master->campus);
	free(master);
}

int ft_freematriz(char **mat)
{
	int i;

	i = -1;
	if (mat != NULL)
	{
		while (mat && mat[++i])
			free(mat[i]);
		free(mat);
	}
	return (i);
}
