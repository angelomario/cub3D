/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:27:28 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/11 10:16:38 by aquissan         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/get_next_line.h"

static void pre_line(char **str, char **line)
{
    char    *nl;
    size_t  len;
    size_t  i;

    nl = ft_strchr(*str, '\n');
    len = ft_strlen(*str) - ft_strlen(nl) + 2;
    *line = (char *)malloc(len * sizeof(char));
    if (!*line)  // Correção: verifica o valor apontado por line
        return;
    i = 0;
    while (i < (len - 1))
    {
        (*line)[i] = (*str)[i];
        i++;
    }
    (*line)[i] = '\0';
}


static void	pos_line(char **str)
{
	char	*nl;
	char	*tmp;
	size_t	i;
	size_t	j;

	nl = ft_strchr(*str, '\n');
	if (!nl)
	{
		free(*str);
		*str = NULL;
		return ;
	}
	tmp = malloc((ft_strlen(nl) + 1) * sizeof(char));
		// Garantindo espaço suficiente
	if (!tmp)                                         // Verificação de malloc
	{
		free(*str);
		*str = NULL;
		return ;
	}
	i = 0;
	j = ft_strlen(*str) - ft_strlen(nl) + 1;
	while (j < ft_strlen(*str))
		tmp[i++] = (*str)[j++];
	tmp[i] = '\0';
	free(*str);
	*str = tmp;
	if (**str == '\0')
	{
		free(*str);
		*str = NULL;
	}
}

static int	getstrbuff(int fd, char **str, char *buffer)
{
	char	*tmp;
	int		bytes;

	ft_bzero(buffer, BUFFER_SIZE + 1);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes < 0) // Correção: se read falhar
	{
		free(*str);
		*str = NULL;
		return (-1);
	}
	if (bytes == 0)
		return (bytes);
	tmp = ft_strjoin(*str, buffer);
	if (!tmp) // Verificação se ft_strjoin falhou
	{
		free(*str);
		*str = NULL;
		return (-1);
	}
	free(*str);
	*str = tmp;
	return (bytes);
}

char	*get_next_line(int fd)
{
	static char	*nxtline;
	char		*line;
	char		*buffer;
	int			bytes;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer) // Verificação de malloc
		return (NULL);
	bytes = 1;
	while (ft_strchr(nxtline, '\n') == NULL && bytes > 0)
		bytes = getstrbuff(fd, &nxtline, buffer);
	free(buffer);
	if (bytes == -1 || !nxtline || ft_strlen(nxtline) == 0) // Correção aqui
	{
		free(nxtline);
		nxtline = NULL;
		return (NULL);
	}
	pre_line(&nxtline, &line);
	pos_line(&nxtline);
	return (line);
}
