/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:42:09 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/11 10:01:45 by aquissan         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/cub3D.h"

int check_filename(char *filename)
{
    int i;
    char *substr;

    i = ft_strlen(filename);
    if (i <= 4)
        return (-1);
    substr = ft_substr(filename, (i - 4), i);
    if (ft_strcmp(substr, ".cub") != 0)
        return (free(substr), -1);
    return (free(substr), 0);
}

t_map   *ft_read_file(char *filepath)
{
    t_map*  map;
    t_map*  tmp;
    char*   str;
	int fd;

    if (check_filename(filepath) == -1)
        return (printf("%s is not a file with a valid map name\n", filepath), NULL);
    fd = open(filepath, READ);
	if (fd == -1)
		return (printf("The map %s cannot be opened or does not exist\n", filepath), NULL);
    map = (t_map *)malloc(sizeof(t_map) * 1);
    map->line = get_next_line(fd);
    map->next = NULL;
    tmp = map;
    while ((str = get_next_line(fd)) != NULL)
    {
        tmp->next = (t_map *)malloc(sizeof(t_map) * 1);
        tmp = tmp->next;
        tmp->line = str;
        tmp->next = NULL;
    }
    free(str);
    close(fd);
	return (map);
}

// int getcolor(char *str)
// {
//     int i;

//     i = 0;
// }
