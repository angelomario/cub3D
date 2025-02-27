/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:00:21 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/27 12:00:54 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double magnitude2D(t_vector vet)
{
  return (sqrt(vet.x * vet.x + vet.y * vet.y));
}

void setWallHeight(t_minilib *render, int hitSide, t_intvector wallMapPos, t_intvector step)
{
  if (hitSide == 0)
    render->perpendicularDist = fabs((wallMapPos.x - render->pos.x + ((1 - step.x) / 2.0)) / render->rayDir.x);
  else
    render->perpendicularDist = fabs((wallMapPos.y - render->pos.y + ((1 - step.y) / 2.0)) / render->rayDir.y);
  render->wallHeight = SCREEN_HEIGHT / render->perpendicularDist;
}

t_vector rotate_vector(t_vector v, double angle)
{
  t_vector rotated;

  rotated.x = v.x * cos(angle) - v.y * sin(angle);
  rotated.y = v.x * sin(angle) + v.y * cos(angle);
  return (rotated);
}