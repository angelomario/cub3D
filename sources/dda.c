/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 11:51:02 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/27 11:59:28 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void dda(t_master *master, t_minilib *render, int *hitSide, t_intvector *step, t_intvector *wallMapPos)
{
	bool hit;
	t_vector ddalinesize;

	ddalinesize = (t_vector){render->distToSide.x, render->distToSide.y};
	*wallMapPos = render->mapPos;
	hit = false;
	while (hit == false)
	{
	if (ddalinesize.x < ddalinesize.y)
	{
		(*wallMapPos).x += step->x;
		ddalinesize.x += render->deltaDist.x;
		*hitSide = 0;
	}
	else
	{
		(*wallMapPos).y += step->y;
		ddalinesize.y += render->deltaDist.y;
		*hitSide = 1;
	}
	if (master->campus[(*wallMapPos).x][(*wallMapPos).y] == '1')
		hit = true;
	}
}
