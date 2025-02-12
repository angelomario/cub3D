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
	t_master	*master;
	t_map		*map;

	if (ac == 2 && av)
	{
		map = ft_read_file(av[1]);
		if (map)
		{
			master = get_master(map);
			printf("%s\n", master->SO);
			printf("%s\n", master->WE);
			printf("%s\n", master->EA);
			printf("%s\n", master->NO);
			printf("%i\n", master->C);
			printf("%i\n", master->F);
			printf("Campus: %s\n", master->campus[1]);
			ft_free_stack(map);
			ft_free_master(master);
		}
		(void)master;
		printf("\n");
	}
	else
	{
		printf("%s--------|  Usage: ./<executable> <map_way>  |--------%s\n",
			RED, RESET);
	}
	return (0);
}
