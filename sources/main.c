/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:29:11 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/11 10:26:18 by aquissan         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3D.h"

int	main(int ac, char *av[])
{
	t_map *map;
	t_map *tmp;

	if (ac == 2 && av)
	{
		map = ft_read_file(av[1]);
		tmp = map;
		while (map)
		{
			printf("%s", map->line);
			map = map->next;
		}
		ft_free_stack(tmp);
		printf("\n");
	}
	else
	{
		printf("%s--------|  Usage: ./<executable> <map_way>  |--------%s\n", RED, RESET);
	}
	return (0);
}
