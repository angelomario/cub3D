/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:42:09 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/17 14:51:28 by aquissan         ###   ########.fr       */
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
	{
		tmp = ft_strjoin(filename, " is not a file with a valid map name");
		printerror(tmp);
		free(tmp);
		return (-1);
	}
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

int	check_elements(t_master *master)
{
	if (!master->so || !master->no || !master->we || !master->ea)
	{
		printerror("Expected SO, NO, WE and EA fields");
		master->wrongmap = 1;
	}
	else if (master->c == -1 || master->f == -1)
	{
		printerror("A valid color was expected for ceil(C) and floor(F)");
		master->wrongmap = 1;
	}
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
		ft_replacestr(&master->so, ft_strdup(sep[1]));
	else if ((ft_countmatriz(sep) == 2) && ft_strcmp(sep[0], "NO") == 0)
		ft_replacestr(&master->no, ft_strdup(sep[1]));
	else if ((ft_countmatriz(sep) == 2) && ft_strcmp(sep[0], "WE") == 0)
		ft_replacestr(&master->we, ft_strdup(sep[1]));
	else if ((ft_countmatriz(sep) == 2) && ft_strcmp(sep[0], "EA") == 0)
		ft_replacestr(&master->ea, ft_strdup(sep[1]));
	else if ((ft_countmatriz(sep) == 2) && ft_strcmp(sep[0], "C") == 0)
		master->c = getcolor(sep[1], master);
	else if ((ft_countmatriz(sep) == 2) && ft_strcmp(sep[0], "F") == 0)
		master->f = getcolor(sep[1], master);
	else if (ft_countmatriz(sep) > 0)
	{
		check_elements(master);
		flag = -1;
	}
	return (ft_freematriz(sep), flag);
}

int	is_there_something_wrong(t_master *master, t_map *map)
{
	if (master->c == -1 || master->f == -1)
		master->wrongmap = 1;
	if (!master->so || !master->ea || !master->we || !master->no)
		master->wrongmap = 1;
	if (!master->campus)
		return (master->wrongmap = 1, printerror("Expected a valid map"), 0);
	while (map && is_voidline(map->line) == 0)
		map = map->next;
	while (map && is_voidline(map->line))
		map = map->next;
	if (map)
	{
		master->wrongmap = 1;
		return (printerror("The map must be the last component"));
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
