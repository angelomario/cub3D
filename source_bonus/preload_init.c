/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preload_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:23:59 by aquissan          #+#    #+#             */
/*   Updated: 2025/05/05 17:21:07 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

int	set_preload_image(t_preload *pl, void *mlx)
{
	int	i;

	i = -1;
	pl->background.img = mlx_xpm_file_to_image(mlx, pl->background.path,
			&pl->background.width, &pl->background.height);
	if (!pl->background.img)
		return (14);
	pl->background.addr = mlx_get_data_addr(pl->background.img,
			&pl->background.bits_per_pixel, &pl->background.line_length,
			&pl->background.endian);
	while (++i < 13)
	{
		pl->logo[i].img = mlx_xpm_file_to_image(mlx, pl->logo[i].path,
				&pl->logo[i].width, &pl->logo[i].height);
		loading();
	}
	while (--i >= 0)
	{
		if (!pl->logo[i].img)
			return (i + 1);
		pl->logo[i].addr = mlx_get_data_addr(pl->logo[i].img,
				&pl->logo[i].bits_per_pixel, &pl->logo[i].line_length,
				&pl->logo[i].endian);
	}
	return (0);
}

int	free_preload(t_preload *preload, void *mlx)
{
	int	start;

	start = 12;
	while (start >= 0)
	{
		if (preload->logo[start].img)
		{
			mlx_destroy_image(mlx, preload->logo[start].img);
			preload->logo[start].img = NULL;
		}
		--start;
	}
	if (preload->background.img)
	{
		mlx_destroy_image(mlx, preload->background.img);
		preload->background.img = NULL;
	}
	if (preload->img)
	{
		mlx_destroy_image(mlx, preload->img);
		preload->img = NULL;
	}
	return (0);
}

int	set_preload_default(t_preload *preload)
{
	int	i;

	i = 0;
	while (i < 13)
	{
		preload->logo[i].img = NULL;
		i++;
	}
	preload->img = NULL;
	preload->background.img = NULL;
	return (0);
}

int	loading(void)
{
	int			i;
	int			total;
	int			perc;
	static int	texture_step;

	texture_step++;
	total = 50;
	perc = (texture_step * total) / QTD_TEXTURE;
	printf("\r%s--|%s", WHITE, RESET);
	i = 0;
	while (i < total)
	{
		if (i < perc)
			printf("%s%s%s", GREEN, BLOCK, RESET);
		else
			printf("%s%s%s", WHITE, BLOCK, RESET);
		i++;
	}
	printf("%s|-| %d%% |--%s", WHITE, (perc * 2), RESET);
	fflush(stdout);
	if ((perc * 2) >= 100)
		printf("\n");
	usleep(10000);
	return (perc);
}
