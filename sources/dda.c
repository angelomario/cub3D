/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:51:02 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/14 11:44:39 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

void	dda(t_master *master, int *hitSide, t_intvector *step,
		t_intvector *wallMapPos)
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
			*hitSide = 0;
		}
		else
		{
			(*wallMapPos).y += step->y;
			ddalinesize.y += master->render.deltadist.y;
			*hitSide = 1;
		}
		if (master->campus[(*wallMapPos).x][(*wallMapPos).y] == '1')
			hit = true;
	}
}
