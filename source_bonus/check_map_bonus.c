/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:42:09 by aquissan          #+#    #+#             */
/*   Updated: 2025/05/08 15:33:26 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

t_map	*ft_read_file(char *filepath)
{
	t_map	*map;
	t_map	*tmp;
	char	*str;
	int		fd;

	if (check_filename(filepath) == -1)
		return (NULL);
	fd = open(filepath, READ);
	if (fd == -1)
		return (printerror(strerror(errno)), NULL);
	map = (t_map *)malloc(sizeof(t_map) * 1);
	map->line = get_next_line(fd);
	map->next = NULL;
	tmp = map;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		tmp->next = (t_map *)malloc(sizeof(t_map) * 1);
		tmp = tmp->next;
		tmp->line = str;
		tmp->next = NULL;
	}
	return (free(str), close(fd), map);
}

int	get_campus(t_map *map, t_master **master)
{
	int		i;
	int		length;
	char	**campus;

	i = 0;
	length = ft_countlinecampus(map);
	if (length >= 3)
	{
		campus = (char **)malloc(sizeof(char *) * (length + 1));
		while (map && i < length)
		{
			ft_replacechar(map->line, '\n', '\0');
			campus[i] = ft_strdup(map->line);
			i++;
			map = map->next;
		}
		campus[length] = NULL;
		(*master)->campus = campus;
		return (0);
	}
	else
		(*master)->campus = NULL;
	return (1);
}

int	check_variables(char *vars, t_master *master)
{
	int	x;
	int	y;
	int	qtd;

	x = -1;
	while (master->campus[++x])
	{
		y = 0;
		while (master->campus[x][y])
		{
			if (ft_strchr(vars, master->campus[x][y]) == NULL)
			{
				master->wrongmap = 1;
				return (-1);
			}
			y++;
		}
	}
	qtd = count_var(master->campus, 'W') + count_var(master->campus, 'N')
		+ count_var(master->campus, 'S') + count_var(master->campus, 'E');
	if (qtd == 0)
		return (master->wrongmap = 1, 1);
	else if (qtd > 1)
		return (master->wrongmap = 1, 2);
	return (0);
}

int	check_campus(t_master *master)
{
	int	indent;

	indent = check_variables(" 10WENSDd", master);
	if (indent == -1)
		return (printerror("A different character on the map"));
	else if (indent == 1)
		return (printerror("Missing player"));
	else if (indent == 2)
		return (printerror("The game must have only one player"));
	if (master->wrongmap == 1)
		return (0);
	if (!have_valid_wall(master->campus))
	{
		master->wrongmap = 1;
		return (printerror("The map must be surrounded by walls"));
	}
	if (around_character(master->campus, master) != 0)
	{
		master->wrongmap = 1;
		printerror("The player must be inside de map");
	}
	return (0);
}

t_master	*get_master(t_map *map)
{
	t_master	*master;
	t_map		*tmp;

	tmp = map;
	master = (t_master *)malloc(sizeof(t_master) * 1);
	initializedefault(master);
	while (tmp)
	{
		if (check_components(tmp->line, master) == -1)
		{
			get_campus(tmp, &master);
			break ;
		}
		tmp = tmp->next;
	}
	if (master->wrongmap)
		return (master);
	is_there_something_wrong(master, tmp);
	if (master->campus && master->wrongmap == 0)
		check_campus(master);
	if (check_door(master->campus) && master->wrongmap == 0)
		return (printerror("Doors must be between walls and inside the map"),
			master->wrongmap = 1, master);
	sound_init(&master->sounds, &master->bass_active);
	return (master->weapon = 0, set_weapon(master, 0), master);
}
