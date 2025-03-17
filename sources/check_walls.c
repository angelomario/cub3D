/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:00:18 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/17 13:25:47 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_around(char **map, int x, int y)
{
	if (((x - 1) < 0) || ((x + 1) >= ft_countline(map)))
		return (0);
	if (map[x - 1] && ((int)ft_strlen(map[x - 1]) > y) && map[x - 1][y] == ' ')
		return (0);
	else if (!map[x - 1] || ((int)ft_strlen(map[x - 1]) <= y))
		return (0);
	if (map[x + 1] && ((int)ft_strlen(map[x + 1]) > y) && map[x + 1][y] == ' ')
		return (0);
	else if (!map[x + 1] || ((int)ft_strlen(map[x + 1]) <= y))
		return (0);
	if (map[x][y - 1] && map[x][y - 1] == ' ')
		return (0);
	else if (map[x][y - 1] == '\0')
		return (0);
	if (map[x][y + 1] && map[x][y + 1] == ' ')
		return (0);
	else if (map[x][y + 1] == '\0')
		return (0);
	return (1);
}

int	around_character(char **tab, t_master *master)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (tab[x])
	{
		y = 0;
		while (tab[x][y] != '\0')
		{
			if (tab[x][y] == 'W' || tab[x][y] == 'N' || tab[x][y] == 'E'
				|| tab[x][y] == 'S')
			{
				if (check_around(tab, x, y) == 0)
					return (master->wrongmap = 1, 1);
			}
			y++;
		}
		x++;
	}
	return (0);
}

int	ft_find_leak(char **tab)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (tab[x])
	{
		y = 0;
		while (tab[x][y] != '\0')
		{
			if (tab[x][y] == '0')
			{
				if (check_around(tab, x, y) == 0)
					return (1);
			}
			y++;
		}
		x++;
	}
	return (0);
}

int	have_valid_wall(char **map)
{
	char	**line;
	int		x;

	x = 0;
	while (map[x] != NULL)
	{
		line = ft_split(map[x], ' ');
		if (ft_orizontalwall(line) == 0)
			return (ft_freematriz(line), 0);
		ft_freematriz(line);
		x++;
	}
	if (ft_find_leak(map) == 1)
		return (0);
	return (1);
}

int	ft_orizontalwall(char **line)
{
	int	i;

	i = 0;
	while (line[i] != NULL)
	{
		if ((line[i][0] != '1') || (line[i][ft_strlen(line[i]) - 1] != '1'))
			return (0);
		i++;
	}
	return (1);
}
