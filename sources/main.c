/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:29:11 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/13 17:36:14 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	show_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		printf("%s%s%s\n", GREEN, map[i], RESET);
		i++;
	}
}

int main(int ac, char *av[])
{
	t_master *master;
	t_map *map;

	if (ac == 2 && av)
	{
		map = ft_read_file(av[1]);
		if (map)
		{
			master = get_master(map);
			if (master->wrongmap == 0)
			{
				printf("%s\n", master->SO);
				printf("%s\n", master->WE);
				printf("%s\n", master->EA);
				printf("%s\n", master->NO);
				printf("%i\n", master->C);
				printf("%i\n", master->F);
				show_map(master->campus);
			}
			else
			{
				printf("%s           -------------%s\n", RED, RESET);
				printf("%s|---------| Invalid map |---------|%s\n", RED, RESET);
				printf("%s           -------------%s\n", RED, RESET);
			}
			ft_free_stack(map);
			ft_free_master(master);
		}
		(void)master;
		printf("\n");
	}
	else
	{
		printf("%s         ---------------------------------%s\n", RED, RESET);
		printf("%s|-------| Usage: ./<executable> <map_way> |-------|%s\n", RED, RESET);
		printf("%s         ---------------------------------%s\n", RED, RESET);
	}
	return (0);
}
