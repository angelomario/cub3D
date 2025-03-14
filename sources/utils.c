/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:42:09 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/14 12:04:17 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
	master->campus = NULL;
	master->keyboard = (t_keyboard){false, false, false, false, false, false,
		false, false};
	return (0);
}
