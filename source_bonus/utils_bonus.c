/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:42:09 by aquissan          #+#    #+#             */
/*   Updated: 2025/05/02 14:41:30 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	is_voidline(char *line)
{
	int	i;

	i = 0;
	if (line)
	{
		while (line[i] && (line[i] == '\t' || line[i] == ' '))
			i++;
		if (line[i] == '\n' || line[i] == '\0')
			return (1);
		else
			return (0);
	}
	return (0);
}

void	ft_replacechar(char *str, char to_find, char to_replace)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] == to_find)
			str[i] = to_replace;
	}
}

int	ft_replacestr(char **str, char *to_replace)
{
	if ((str && *str) && to_replace)
	{
		free(*str);
		*str = to_replace;
		return (0);
	}
	if (to_replace)
		*str = to_replace;
	return (-1);
}

int	ft_countlinecampus(t_map *list)
{
	int	i;

	i = 0;
	while (list && !is_voidline(list->line))
	{
		i++;
		list = list->next;
	}
	return (i);
}

int	initializedefault(t_master *master)
{
	master->c = -1;
	master->f = -1;
	master->wrongmap = 0;
	master->so = NULL;
	master->we = NULL;
	master->ea = NULL;
	master->no = NULL;
	master->index_door = 0;
	master->campus = NULL;
	master->keyboard = (t_keyboard){false, false, false, false, false, false,
		false, false, false, false, false, false};
	master->view_high = 0;
	master->dimension = (t_3d){0, 2, 0};
	master->time_animation = 0;
	master->limit_time_animation = 10;
	master->door_time_animation = 0;
	master->door_limit_time_animation = 0;
	master->focused_open_door = (t_intvector){-1, -1};
	master->focused_close_door = (t_intvector){-1, -1};
	master->wait_to_close_the_door = 0;
	master->data_root_door = NULL;
	master->data_door = NULL;
	master->game_started = false;
	return (0);
}
