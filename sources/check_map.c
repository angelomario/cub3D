/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:42:09 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/26 11:51:48 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_map *ft_read_file(char *filepath)
{
    t_map *map;
    t_map *tmp;
    char *str;
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

int get_campus(t_map *map, t_master **master)
{
    int i;
    int length;
    char **campus;

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
    (*master)->wrongmap = 1;
    return (1);
}

int check_variables(char *vars, t_master *master)
{
    int x;
    int y;

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
    if ((count_var(master->campus, 'W') + count_var(master->campus, 'N') + count_var(master->campus, 'S') + count_var(master->campus, 'E')) != 1)
        return (master->wrongmap = 1, 1);
    return (0);
}

int check_campus(t_master *master)
{
    check_variables(" 10WENS", master);
    if (master->wrongmap == 1)
        return (0);
    if (!have_valid_wall(master->campus))
        master->wrongmap = 1;
    around_character(master->campus, master);
    return (0);
}

t_master *get_master(t_map *map)
{
    t_master *master;
    t_map *tmp;

    tmp = map;
    master = (t_master *)malloc(sizeof(t_master) * 1);
    initializedefault(master);
    while (tmp)
    {
        if (check_components(tmp->line, master) == -1)
        {
            get_campus(tmp, &master);
            break;
        }
        tmp = tmp->next;
    }
    is_there_something_wrong(master, tmp);
    if (master->campus)
        check_campus(master);
    return (master);
}
