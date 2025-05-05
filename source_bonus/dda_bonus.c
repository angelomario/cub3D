/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <nmatondo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:51:02 by aquissan          #+#    #+#             */
/*   Updated: 2025/04/17 15:30:10 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	ft_countchar(char *str, char ch)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] == ch)
				len++;
			i++;
		}
	}
	return (len);
}

int	correct_color(char *str)
{
	if (ft_countchar(str, ',') > 2 || ft_strchr(str, '\"') || ft_strchr(str,
			'\''))
		return (-1);
	return (0);
}

int	getcolor(char *str, t_master *master)
{
	int		r;
	int		g;
	int		b;
	char	**rgb;

	if (correct_color(str) != 0)
		return (-1);
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
		if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
			return (ft_freematriz(rgb), -1);
		if (r < 0 || g < 0 || b < 0)
			master->wrongmap = 1;
		return (ft_freematriz(rgb), (r << 16 | g << 8 | b));
	}
	return (-1);
}

void	dda(t_master *master, t_intvector *step, t_intvector *wallMapPos)
{
	bool		hit;
	t_vector	ddalinesize;

	ddalinesize = (t_vector){master->render.disttoside.x,
		master->render.disttoside.y};
	*wallMapPos = master->render.mappos;
	hit = false;
	while (hit == false)
	{
		if (ddalinesize.x < ddalinesize.y)
		{
			(*wallMapPos).x += step->x;
			ddalinesize.x += master->render.deltadist.x;
			master->wall_hitside = 0;
		}
		else
		{
			(*wallMapPos).y += step->y;
			ddalinesize.y += master->render.deltadist.y;
			master->wall_hitside = 1;
		}
		if (master->campus[(*wallMapPos).x][(*wallMapPos).y] == '1')
			hit = true;
	}
}
