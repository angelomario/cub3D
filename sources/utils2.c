/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:04:41 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/14 17:06:04 by aquissan         ###   ########.fr       */
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
