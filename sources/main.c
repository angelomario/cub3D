/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:29:11 by aquissan          #+#    #+#             */
/*   Updated: 2025/03/18 14:37:21 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	key_hook(int keycode, t_master *master)
{
	if (keycode == ESC)
	{
		free_textures(master);
		mlx_destroy_image(master->render.mlx, master->img.img);
		mlx_destroy_window(master->render.mlx, master->render.win);
		mlx_destroy_display(master->render.mlx);
		return (free(master->render.mlx), ft_free_master(master), exit(0), 0);
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

int	ft_game(t_master *master)
{
	t_minilib	render;
	t_data		img;

	render = set_cardial(master);
	render.pos = get_player_pos(master->campus);
	render.pos = (t_vector){render.pos.x + 0.5, render.pos.y + 0.5};
	render.mlx = mlx_init();
	if (!render.mlx)
		return (ft_free_master(master), printerror("Display property no set"),
			1);
	if (load_textures(render.mlx, &img, master))
		return (mlx_destroy_display(render.mlx), free(render.mlx),
			ft_free_master(master), exit(1), 1);
	render.win = mlx_new_window(render.mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"ODYSSEY");
	img.img = mlx_new_image(render.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	master->render = render;
	master->img = img;
	wait_hooks(master);
	mlx_loop_hook(master->render.mlx, controls, master);
	renderization(&master->render, master, &img);
	mlx_put_image_to_window(master->render.mlx, render.win, img.img, 0, 0);
	return (mlx_loop(render.mlx), 0);
}

int	main(int ac, char *av[])
{
	t_master	*master;
	t_map		*map;

	if (ac == 2 && av)
	{
		if (SCREEN_WIDTH < 150)
			return (printerror("Window width too small"), 1);
		if (SCREEN_HEIGHT < 150)
			return (printerror("Window height too small"), 1);
		if (SPEED <= 0)
			return (printerror("The player speed must be bigger than 0"), 1);
		map = ft_read_file(av[1]);
		if (!map)
			return (1);
		master = get_master(map);
		ft_free_stack(map);
		if (master->wrongmap == 0)
			return (ft_game(master));
		else
			return (ft_free_master(master), 1);
	}
	else
		return (printerror("Usage: ./<executable> <map_way>"), 1);
	return (0);
}
