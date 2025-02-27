/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:29:11 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/27 12:00:50 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int key_hook(int keycode, t_master *master)
{
  if (keycode == ESC)
  {
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

int key_release(int keycode, t_master *master)
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

t_minilib set_cardial(t_master *master)
{
  t_minilib render;
  t_vector pos;

  pos = get_player_pos(master->campus);
  if (master->campus[(int)floor(pos.x)][(int)floor(pos.y)] == 'N')
  {
    render.dir = (t_vector){-1, 0};
    render.plane = (t_vector){0, 0.66};
  }
  if (master->campus[(int)floor(pos.x)][(int)floor(pos.y)] == 'S')
  {
    render.dir = (t_vector){1, 0};
    render.plane = (t_vector){0, -0.66};
  }
  if (master->campus[(int)floor(pos.x)][(int)floor(pos.y)] == 'E')
  {
    render.dir = (t_vector){0, 1};
    render.plane = (t_vector){0.66, 0};
  }
  if (master->campus[(int)floor(pos.x)][(int)floor(pos.y)] == 'W')
  {
    render.dir = (t_vector){0, -1};
    render.plane = (t_vector){-0.66, 0};
  }
  return (render);
}

void ft_game(t_master *master)
{
  t_minilib render;
  t_data img;

  show_map(master->campus);
  render = set_cardial(master);
  render.pos = get_player_pos(master->campus);
  render.pos = (t_vector){render.pos.x + 0.5, render.pos.y + 0.5};
  render.mlx = mlx_init();
  render.win = mlx_new_window(render.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Odyssey");
  img.img = mlx_new_image(render.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
  master->render = render;
  master->img = img;
  mlx_hook(master->render.win, 2, 1L << 0, key_hook, master);
  mlx_hook(master->render.win, 3, 1L << 1, key_release, master);
  mlx_loop_hook(master->render.mlx, controls, master);
  renderization(&master->render, master, &img);
  mlx_put_image_to_window(master->render.mlx, render.win, img.img, 0, 0);
  mlx_loop(render.mlx);
}

int main(int ac, char *av[])
{
  t_master *master;
  t_map *map;

  if (ac == 2 && av)
  {
    map = ft_read_file(av[1]);
    master = get_master(map);
    ft_free_stack(map);
    if (master->wrongmap == 0)
      ft_game(master);
    else
    {
      printf("%s           -------------%s\n", RED, RESET);
      printf("%s|---------| Invalid map |---------|%s\n", RED, RESET);
      printf("%s           -------------%s\n", RED, RESET);
      ft_free_master(master);
    }
  }
  else
  {
    printf("%s         ---------------------------------%s\n", RED, RESET);
    printf("%s|-------| Usage: ./<executable> <map_way> |-------|%s\n", RED, RESET);
    printf("%s         ---------------------------------%s\n", RED, RESET);
  }
  return (0);
}
