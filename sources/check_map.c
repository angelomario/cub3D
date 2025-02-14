/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:42:09 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/14 13:18:01 by aquissan         ###   ########.fr       */
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
    return (0);
}

int check_campus(t_master *master)
{
    check_variables(" 10WENS", master);
    if (master->wrongmap == 1)
        return (0);
    if (!have_valid_wall(master->campus))
        master->wrongmap = 1;
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

// ACC

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

int ft_orizontalwall(char **line)
{
    int i;

    i = 0;
    while (line[i] != NULL)
    {
        if ((line[i][0] != '1') || (line[i][ft_strlen(line[i]) - 1] != '1'))
            return (0);
        i++;
    }
    return (1);
}

int deeper(char **mat, int y, int *stop)
{
    int top;
    int down;

    down = *stop;
    top = *stop;
    if (top-- > 0)
    {
        while (top > 0 && ((int)ft_strlen(mat[top]) > y) && mat[top][y] != ' ')
            --top;
        if ((top + 1) < *stop)
            return (*stop = top, 1);
    }
    if (mat[*stop][y] != '\0' && mat[*stop][y] == ' ')
    {
        down++;
        while (ft_countline(mat) > down)
        {
            if (((int)ft_strlen(mat[down]) > y) && mat[down][y] != ' ')
                return (*stop = down, 1);
            down++;
        }
    }
    return (1);
}

int ft_vertical(char **mat)
{
    int y;
    int stop;
    int sbottom;

    sbottom = ft_countline(mat);
    stop = 0;
    y = -1;
    while (mat[stop][++y] != '\0')
    {
        if (deeper(mat, y, &stop) == 0)
            return (0);
        if (mat[stop][y] == '0')
            return (0);
    }
    y = -1;
    --sbottom;
    if (mat[sbottom])
    {
        while (mat[sbottom][++y] != '\0')
        {
            if (mat[sbottom][y] == '0')
                return (0);
        }
    }
    return (1);
}

int have_valid_wall(char **map)
{
    char **line;
    int x;

    x = 0;
    while (map[x] != NULL)
    {
        line = ft_split(map[x], ' ');
        if (ft_orizontalwall(line) == 0)
            return (ft_freematriz(line), 0);
        ft_freematriz(line);
        x++;
    }
    if (ft_vertical(map) == 0)
        return (0);
    return (1);
}
