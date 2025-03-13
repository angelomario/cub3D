/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:42:09 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/13 17:58:16 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_filename(char *filename)
{
	int		i;
	char	*substr;
	char	*tmp;

	i = ft_strlen(filename);
	if (i <= 4)
		return (-1);
	substr = ft_substr(filename, (i - 4), i);
	if (ft_strcmp(substr, ".cub") != 0)
	{
		tmp = ft_strjoin(filename, " is not a file with a valid map name");
		printerror(tmp);
		free(tmp);
		return (free(substr), -1);
	}
	return (free(substr), 0);
}

int	getcolor(char *str, t_master *master)
{
	int		r;
	int		g;
	int		b;
	char	**rgb;

	if (str)
	{
		rgb = ft_split(str, ',');
		if (ft_countmatriz(rgb) != 3)
		{
			master->wrongmap = 1;
			return (ft_freematriz(rgb), -1);
		}
		r = ft_atoi(rgb[0]);
		g = ft_atoi(rgb[1]);
		b = ft_atoi(rgb[2]);
		if (r < 0 || g < 0 || b < 0)
			master->wrongmap = 1;
		return (ft_freematriz(rgb), (r << 16 | g << 8 | b));
	}
	return (-1);
}

int	check_elements(t_master *master)
{
	if (!master->SO || !master->NO || !master->WE || !master->EA)
		printerror("Expected correct values ​​for SO, NO, WE and EA fields");
	else if (master->C == -1 || master->F == -1)
		printerror("A valid color was expected for ceil and floor");
	return (0);
}

int	check_components(char *line, t_master *master)
{
	int		flag;
	char	**sep;

	ft_replacechar(line, '\t', ' ');
	ft_replacechar(line, '\n', ' ');
	sep = ft_split(line, ' ');
	flag = 0;
	if (ft_countmatriz(sep) == 2 && ft_strcmp(sep[0], "SO") == 0)
		ft_replacestr(&master->SO, ft_strdup(sep[1]));
	else if ((ft_countmatriz(sep) == 2) && ft_strcmp(sep[0], "NO") == 0)
		ft_replacestr(&master->NO, ft_strdup(sep[1]));
	else if ((ft_countmatriz(sep) == 2) && ft_strcmp(sep[0], "WE") == 0)
		ft_replacestr(&master->WE, ft_strdup(sep[1]));
	else if ((ft_countmatriz(sep) == 2) && ft_strcmp(sep[0], "EA") == 0)
		ft_replacestr(&master->EA, ft_strdup(sep[1]));
	else if ((ft_countmatriz(sep) == 2) && ft_strcmp(sep[0], "C") == 0)
		master->C = getcolor(sep[1], master);
	else if ((ft_countmatriz(sep) == 2) && ft_strcmp(sep[0], "F") == 0)
		master->F = getcolor(sep[1], master);
	else if (ft_countmatriz(sep) > 0)
	{
		check_elements(master);
		flag = -1;
	}
	return (ft_freematriz(sep), flag);
}

int	is_there_something_wrong(t_master *master, t_map *map)
{
	if (master->C == -1 || master->F == -1)
		master->wrongmap = 1;
	if (!master->SO || !master->EA || !master->WE || !master->NO)
		master->wrongmap = 1;
	while (map && is_voidline(map->line) == 0)
		map = map->next;
	if (!map)
		return (master->wrongmap = 1, printerror("Expected map"), 0);
	if (master->campus == NULL)
	{
		master->wrongmap = 1;
		printerror("Invalid map");
	}
	return (0);
}

int	ft_countmatriz(char **mat)
{
	int	i;

	i = 0;
	while (mat && mat[i])
		i++;
	return (i);
}
