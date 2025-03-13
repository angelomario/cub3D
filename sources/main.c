/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:29:11 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/13 17:57:59 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_textures(t_master *master)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(master->render.mlx, master->img.textures[i]);
		i++;
	}
}

int	key_hook(int keycode, t_master *master)
{
	if (keycode == ESC)
	{
		free_textures(master);
		mlx_destroy_image(master->render.mlx, master->img.img);
		mlx_destroy_window(master->render.mlx, master->render.win);
		mlx_destroy_display(master->render.mlx);
		free(master->render.mlx);
		return (ft_free_master(master), exit(0), 0);
	}
	if (keycode == RRIGHT)
		master->keyboard.r_right = true;
	if (keycode == RUP)
		master->keyboard.r_up = true;
	if (keycode == RDOWN)
		master->keyboard.r_down = true;
	if (keycode == RLEFT)
		master->keyboard.r_left = true;
	if (keycode == RIGHT)
		master->keyboard.right = true;
	if (keycode == DOWN)
		master->keyboard.down = true;
	if (keycode == UP)
		master->keyboard.up = true;
	if (keycode == LEFT)
		master->keyboard.left = true;
	return (0);
}

int	key_release(int keycode, t_master *master)
{
	if (keycode == RRIGHT)
		master->keyboard.r_right = false;
	if (keycode == RUP)
		master->keyboard.r_up = false;
	if (keycode == RDOWN)
		master->keyboard.r_down = false;
	if (keycode == RLEFT)
		master->keyboard.r_left = false;
	if (keycode == RIGHT)
		master->keyboard.right = false;
	if (keycode == DOWN)
		master->keyboard.down = false;
	if (keycode == UP)
		master->keyboard.up = false;
	if (keycode == LEFT)
		master->keyboard.left = false;
	return (0);
}

t_minilib	set_cardial(t_master *master)
{
	t_minilib	render;
	t_vector	pos;

	pos = get_player_pos(master->campus);
	if (master->campus[(int)pos.x][(int)pos.y] == 'N')
	{
		render.dir = (t_vector){-1, 0};
		render.plane = (t_vector){0, 0.66};
	}
	if (master->campus[(int)pos.x][(int)pos.y] == 'S')
	{
		render.dir = (t_vector){1, 0};
		render.plane = (t_vector){0, -0.66};
	}
	if (master->campus[(int)pos.x][(int)pos.y] == 'E')
	{
		render.dir = (t_vector){0, 1};
		render.plane = (t_vector){0.66, 0};
	}
	if (master->campus[(int)pos.x][(int)pos.y] == 'W')
	{
		render.dir = (t_vector){0, -1};
		render.plane = (t_vector){-0.66, 0};
	}
	return (render);
}

void	msg_error_image_not_found(int i, void *mlx, t_data *img)
{
	printerror("Incorrect texture");
	while ((i - 1 >= 0) && img->textures[i - 1])
	{
		mlx_destroy_image(mlx, img->textures[i - 1]);
		i--;
	}
}

int	load_textures(void *mlx, t_data *img, t_master *master)
{
	int	i;

	i = 0;
	img->tex_paths[0] = master->NO;
	img->tex_paths[1] = master->SO;
	img->tex_paths[2] = master->WE;
	img->tex_paths[3] = master->EA;
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

int	ft_game(t_master *master)
{
	t_minilib	render;
	t_data		img;

	show_map(master->campus);
	render = set_cardial(master);
	render.pos = get_player_pos(master->campus);
	render.pos = (t_vector){render.pos.x + 0.5, render.pos.y + 0.5};
	render.mlx = mlx_init();
	if (load_textures(render.mlx, &img, master))
	{
		mlx_destroy_display(render.mlx);
		return (free(render.mlx), ft_free_master(master), exit(1), 1);
	}
	render.win = mlx_new_window(render.mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"Odyssey");
	img.img = mlx_new_image(render.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	master->render = render;
	master->img = img;
	mlx_hook(master->render.win, 2, 1L << 0, key_hook, master);
	mlx_hook(master->render.win, 3, 1L << 1, key_release, master);
	mlx_loop_hook(master->render.mlx, controls, master);
	renderization(&master->render, master, &img);
	mlx_put_image_to_window(master->render.mlx, render.win, img.img, 0, 0);
	return (mlx_loop(render.mlx), 0);
}

int	printerror(char *str)
{
	char	*tmp1;
	char	*tmp2;

	if (str)
	{
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

int	main(int ac, char *av[])
{
	t_master	*master;
	t_map		*map;

	if (ac == 2 && av)
	{
		map = ft_read_file(av[1]);
		master = get_master(map);
		ft_free_stack(map);
		if (master->wrongmap == 0)
			ft_game(master);
		else
		{
			ft_free_master(master);
		}
	}
	else
		printerror("Usage: ./<executable> <map_way>");
	return (0);
}
