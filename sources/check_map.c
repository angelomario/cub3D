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

int	is_voidline(char *line)
{
    int i;

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


void    ft_replacechar(char *str, char to_find, char to_replace)
{
    int i;

    i = -1;
    while (str && str[++i])
    {
        if (str[i] == to_find)
            str[i] = to_replace;
    }
}

int ft_countmatriz(char **mat)
{
    int i;

    i = 0;
    while (mat && mat[i])
        i++;
    return (i);
}

int getcolor(char *str)
{
    int r;
    int g;
    int b;
    char    **rgb;

    if (str)
    {
        rgb = ft_split(str, ',');
        if (ft_countmatriz(rgb) != 3)
            return (ft_freematriz(rgb), -1);
        r = ft_atoi(rgb[0]);
        g = ft_atoi(rgb[1]);
        b = ft_atoi(rgb[2]);
        return (ft_freematriz(rgb), (r << 16 | g << 8 | b));
    }
    return (-1);
}

int ft_replacestr(char **str, char *to_replace)
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

int check_components(char *line, t_master *master)
{
    int flag;
    char **sep;

    ft_replacechar(line, '\t', ' ');
    ft_replacechar(line, '\n', ' ');
    sep = ft_split(line, ' ');
    flag = 0;
    if (ft_countmatriz(sep) == 2 && ft_strcmp(sep[0], "SO") == 0)
        ft_replacestr(&master->SO, ft_strdup(sep[1]));
    else if ((ft_countmatriz(sep) == 2) && ft_strcmp(sep[0], "NO") == 0)
        ft_replacestr(&master->NO, ft_strdup(sep[1]));
    else if ((ft_countmatriz(sep) == 2) && ft_strcmp(sep[0], "WE") == 0)
        ft_replacestr(&master->WE, ft_strdup(sep[1]));
    else if ((ft_countmatriz(sep) == 2) && ft_strcmp(sep[0], "EA") == 0)
        ft_replacestr(&master->EA, ft_strdup(sep[1]));
    else if ((ft_countmatriz(sep) == 2) && ft_strcmp(sep[0], "C") == 0)
        master->C = getcolor(sep[1]);
    else if ((ft_countmatriz(sep) == 2) && ft_strcmp(sep[0], "F") == 0)
        master->F = getcolor(sep[1]);
    else if (ft_countmatriz(sep) > 0)
        flag = -1;
    return (ft_freematriz(sep), flag);
}

int ft_countlinecampus(t_map *list)
{
    int i;

    i = 0;
    while (list && !is_voidline(list->line))
    {
        i++;
        list = list->next;
    }
    return (i);
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
    return (-1);
}

t_master*   get_master(t_map *map)
{
    t_master *master;
    t_map *tmp;

    tmp = map;
    master = (t_master *)malloc(sizeof(t_master) * 1);
    master->SO = NULL;
    master->WE = NULL;
    master->EA = NULL;
    master->NO = NULL;
    master->campus = NULL;
    while (tmp)
    {
        if (check_components(tmp->line, master) == -1)
        {
            get_campus(tmp, &master);
            break ;
        }
        tmp = tmp->next;
    }
    return (master);
}
