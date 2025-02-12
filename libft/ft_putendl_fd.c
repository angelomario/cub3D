/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:07:56 by aquissan          #+#    #+#             */
/*   Updated: 2024/05/16 16:08:38 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int		i;
	char	ch;

	i = 0;
	ch = '\n';
	while (s[i] != '\0')
		i++;
	write(fd, s, i);
	write(fd, &ch, 1);
}
