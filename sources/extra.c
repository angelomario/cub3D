/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:00:21 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/17 15:31:58 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	setwallheight(t_minilib *render, int hitside, t_intvector wallmappos,
		t_intvector step)
{
	if (hitside == 0)
		render->perpendiculardist = fabs((wallmappos.x - render->pos.x + ((1
							- step.x) / 2.0)) / render->raydir.x);
	else
		render->perpendiculardist = fabs((wallmappos.y - render->pos.y + ((1
							- step.y) / 2.0)) / render->raydir.y);
	render->wallheight = SCREEN_HEIGHT / render->perpendiculardist;
}

t_vector	rotate_vector(t_vector v, double angle)
{
	t_vector	rotated;

	rotated.x = v.x * cos(angle) - v.y * sin(angle);
	rotated.y = v.x * sin(angle) + v.y * cos(angle);
	return (rotated);
}

void	msg_error_image_not_found(int i, void *mlx, t_data *img)
{
	char	*tmp;

	if (i >= 0 && i < 4)
	{
		if (i == 0)
			tmp = ft_strjoin("Incorrect texture ", "NO, it must be xpm type");
		if (i == 1)
			tmp = ft_strjoin("Incorrect texture ", "SO, it must be xpm type");
		if (i == 2)
			tmp = ft_strjoin("Incorrect texture ", "WE, it must be xpm type");
		if (i == 3)
			tmp = ft_strjoin("Incorrect texture ", "EA, it must be xpm type");
		printerror(tmp);
		free(tmp);
	}
	while ((i - 1 >= 0) && img->textures[i - 1])
	{
		mlx_destroy_image(mlx, img->textures[i - 1]);
		i--;
	}
}

int	printerror(char *str)
{
	char	*tmp1;
	char	*tmp2;

	if (str)
	{
		ft_putstr_fd("\033[31mError\n\033[0m", 2);
		tmp1 = ft_strjoin(RED, "|-------| ");
		tmp2 = ft_strjoin(tmp1, str);
		free(tmp1);
		tmp1 = ft_strjoin(tmp2, " |-------|\n");
		free(tmp2);
		tmp2 = ft_strjoin(tmp1, RESET);
		ft_putstr_fd(tmp2, 2);
		free(tmp1);
		free(tmp2);
	}
	return (0);
}

int	load_textures(void *mlx, t_data *img, t_master *master)
{
	int	i;

	i = 0;
	img->tex_paths[0] = master->no;
	img->tex_paths[1] = master->so;
	img->tex_paths[2] = master->we;
	img->tex_paths[3] = master->ea;
	while (i < 4)
	{
		img->textures[i] = mlx_xpm_file_to_image(mlx, img->tex_paths[i],
				&img->tex_width[i], &img->tex_height[i]);
		if (!img->textures[i])
			return (msg_error_image_not_found(i, mlx, img), 1);
		img->tex_addr[i] = mlx_get_data_addr(img->textures[i],
				&img->tex_bits_per_pixel[i], &img->tex_line_length[i],
				&img->tex_endian[i]);
		i++;
	}
	return (0);
}
