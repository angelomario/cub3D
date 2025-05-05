/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:29:11 by aquissan          #+#    #+#             */
/*   Updated: 2025/05/05 12:04:44 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

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

	init_data_struct(&img);
	render = set_cardial(master);
	render.pos = get_player_pos(master->campus);
	render.pos = (t_vector){render.pos.x + 0.5, render.pos.y + 0.5};
	render.mlx = mlx_init();
	if (!render.mlx)
		return (ft_free_master(master), printerror("Connection mlx failed"), 1);
	if (load_all_texteres(render.mlx, &img, master))
		return (mlx_destroy_display(render.mlx), free(render.mlx),
			ft_free_master(master), exit(1), 1);
	render.win = mlx_new_window(render.mlx, SCREEN_WIDTH, SCREEN_HEIGHT,
			"ODYSSEY 2.0");
	img.img = mlx_new_image(render.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	master->render = render;
	master->img = img;
	if (master->game_started)
		mlx_put_image_to_window(master->render.mlx, render.win, img.img, 0, 0);
	return (wait_hooks(master), mlx_loop_hook(master->render.mlx, controls,
			master), mlx_loop(render.mlx), 0);
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
		master->rotate_angle = 0;
		if (master->wrongmap == 0)
			return (ft_game(master));
		else
			return (ft_free_master(master), 1);
	}
	else
		return (printerror("Usage: ./<executable> <map_way>"), 1);
	return (0);
}
