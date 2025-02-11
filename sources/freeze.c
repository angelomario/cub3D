/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeze.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:20:22 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/11 10:25:51 by aquissan         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3D.h"

void	ft_free_stack(t_map *map)
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