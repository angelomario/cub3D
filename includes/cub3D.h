/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:31:28 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/11 10:24:29 by aquissan         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#ifndef CUB3D_H
# define CUB3D_H

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define READ O_RDONLY
# define WRITE O_WRONLY
# include "../libft/libft.h"
# include "get_next_line.h"

typedef struct s_map
{
	char			*line;
	struct s_map	*next;
}					t_map;

typedef struct s_master
{
	int				C;
	int				F;
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;

	char			**map;
}					t_master;

// FUNCTIONS
t_map				*ft_read_file(char *filepath);

// FREEZE
void				ft_free_stack(t_map *map);

#endif