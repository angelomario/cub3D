/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:04:41 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/27 11:56:06 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int ft_countline(char **map)
{
    int i;

    i = 0;
    if (map == NULL || *map == NULL)
        return (0);
    while (map[i] != NULL)
        i++;
    return (i);
}

int count_var(char **map, char var)
{
    int x;
    int y;
    int qtd_var;

    qtd_var = 0;
    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == var)
                qtd_var++;
            x++;
        }
        y++;
    }
    return (qtd_var);
}

t_vector get_player_pos(char **campus)
{
    int x;
    int y;

    x = 0;
    while (campus[x])
    {
        y = 0;
        while (campus[x][y])
        {
            if (campus[x][y] == 'N' || campus[x][y] == 'W' || campus[x][y] == 'E' || campus[x][y] == 'S')
                return ((t_vector){x, y});
            y++;
        }
        x++;
    }
    return ((t_vector){0, 0});
}

t_vector setDeltaDist(t_vector rayDir)
{
    t_vector deltaDist;

    if (rayDir.x == 0)
    {
        deltaDist.x = 1;
        deltaDist.y = 0;
    }
    else if (rayDir.y == 0)
    {
        deltaDist.x = 0;
        deltaDist.y = 1;
    }
    else
    {
        deltaDist.x = fabs(1 / rayDir.x);
        deltaDist.y = fabs(1 / rayDir.y);
    }
    return (deltaDist);
}

t_vector set_distToSide(t_intvector *step, t_vector rayDir, t_minilib *render, t_intvector mapPos)
{
    t_vector distToSide;

    if (rayDir.x < 0)
    {
        distToSide.x = (render->pos.x - mapPos.x) * render->deltaDist.x;
        step->x = -1;
    }
    else
    {
        distToSide.x = (mapPos.x + 1 - render->pos.x) * render->deltaDist.x;
        step->x = 1;
    }
    if (rayDir.y < 0)
    {
        distToSide.y = (render->pos.y - mapPos.y) * render->deltaDist.y;
        step->y = -1;
    }
    else
    {
        distToSide.y = (mapPos.y + 1 - render->pos.y) * render->deltaDist.y;
        step->y = 1;
    }
    return (distToSide);
}
