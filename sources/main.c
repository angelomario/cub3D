/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:29:11 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/26 17:57:20 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void show_map(char **map)
{
  int i;

  i = 0;
  while (map && map[i])
  {
    printf("%s%s%s\n", GREEN, map[i], RESET);
    i++;
  }
}

double magnitude2D(t_vector vet)
{
  return (sqrt(vet.x * vet.x + vet.y * vet.y));
}

t_vector setDeltaDist(t_vector rayDir)
{
  t_vector deltaDist;

  if (rayDir.x == 0)
  {
    deltaDist.x = 1;
    deltaDist.y = 0;
  }
  else if (rayDir.y == 0)
  {
    deltaDist.x = 0;
    deltaDist.y = 1;
  }
  else
  {
    deltaDist.x = fabs(1 / rayDir.x);
    deltaDist.y = fabs(1 / rayDir.y);
  }
  return (deltaDist);
}

void draw(int lineHeight, int hitSide, int x, t_data *img)
{
  (void)hitSide;
  int y;

  y = (SCREEN_HEIGHT / 2) - (lineHeight / 2);
  if (y < 0)
    y = 0;
  while (y < SCREEN_HEIGHT && lineHeight)
  {
    my_mlx_pixel_put(img, x, y, 0x00ff0000);
    lineHeight--;
    y++;
  }
}

// void draw(int lineHeight, int hitSide, int x, t_data *img)
// {
//   int y;
//   int drawStart;
//   int drawEnd;

//   drawStart = (SCREEN_HEIGHT / 2) - (lineHeight / 2);
//   drawEnd = (SCREEN_HEIGHT / 2) + (lineHeight / 2);
//   if (drawStart < 0)
//     drawStart = 0;
//   if (drawEnd > SCREEN_HEIGHT)
//     drawEnd = SCREEN_HEIGHT;

//   y = drawStart;
//   while (y < drawEnd)
//   {
//     if (hitSide)
//       my_mlx_pixel_put(img, x, y, 0xa60000);
//     else
//       my_mlx_pixel_put(img, x, y, 0x7b0000);
//     y++;
//   }
// }

t_vector set_distToSide(t_intvector *step, t_vector rayDir, t_minilib *render, t_intvector mapPos)
{
  t_vector distToSide;

  if (rayDir.x < 0)
  {
    distToSide.x = (render->pos.x - mapPos.x) * render->deltaDist.x;
    step->x = -1;
  }
  else
  {
    distToSide.x = (mapPos.x + 1 - render->pos.x) * render->deltaDist.x;
    step->x = 1;
  }
  if (rayDir.y < 0)
  {
    distToSide.y = (render->pos.y - mapPos.y) * render->deltaDist.y;
    step->y = -1;
  }
  else
  {
    distToSide.y = (mapPos.y + 1 - render->pos.y) * render->deltaDist.y;
    step->y = 1;
  }
  return (distToSide);
}

void dda(t_master *master, t_minilib *render, int *hitSide, t_intvector *step, t_intvector *wallMapPos)
{
  bool hit;
  t_vector ddalinesize;

  ddalinesize = (t_vector){render->distToSide.x, render->distToSide.y};
  *wallMapPos = render->mapPos;
  hit = false;
  while (hit == false)
  {
    if (ddalinesize.x < ddalinesize.y)
    {
      (*wallMapPos).x += step->x;
      ddalinesize.x += render->deltaDist.x;
      *hitSide = 0;
    }
    else
    {
      (*wallMapPos).y += step->y;
      ddalinesize.y += render->deltaDist.y;
      *hitSide = 1;
    }
    if (master->campus[(*wallMapPos).x][(*wallMapPos).y] == '1')
      hit = true;
  }
}

void setWallHeight(t_minilib *render, int hitSide, t_intvector wallMapPos, t_intvector step)
{
  if (hitSide == 0)
    render->perpendicularDist = fabs((wallMapPos.x - render->pos.x + ((1 - step.x) / 2.0)) / render->rayDir.x);
  else
    render->perpendicularDist = fabs((wallMapPos.y - render->pos.y + ((1 - step.y) / 2.0)) / render->rayDir.y);
  render->wallHeight = SCREEN_HEIGHT / render->perpendicularDist;
}

void renderization(t_minilib *render, t_master *master, t_data *img)
{
  int x;
  double multiple;
  t_vector pixelCam;
  t_intvector step;
  int hitSide;
  t_intvector wallMapPos;

  x = 0;
  clear(img);
  while (x < SCREEN_WIDTH)
  {
    multiple = 2 * ((double)x / SCREEN_WIDTH) - 1;
    pixelCam = (t_vector){render->plane.x * multiple, render->plane.y * multiple};
    render->rayDir = (t_vector){render->dir.x + pixelCam.x, render->dir.y + pixelCam.y};
    render->deltaDist = setDeltaDist(render->rayDir);
    render->mapPos = (t_intvector){(int)floor(render->pos.x), (int)floor(render->pos.y)};
    render->distToSide = set_distToSide(&step, render->rayDir, render, render->mapPos);
    dda(master, render, &hitSide, &step, &wallMapPos);
    setWallHeight(render, hitSide, wallMapPos, step);
    draw(render->wallHeight, hitSide, x, img);
    x++;
  }
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
  char *dst;

  dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
  *(unsigned int *)dst = color;
}

t_vector get_player_pos(char **campus)
{
  int x;
  int y;

  x = 0;
  while (campus[x])
  {
    y = 0;
    while (campus[x][y])
    {
      if (campus[x][y] == 'N' || campus[x][y] == 'W' || campus[x][y] == 'E' || campus[x][y] == 'S')
        return ((t_vector){x, y});
      y++;
    }
    x++;
  }
  return ((t_vector){0, 0});
}

t_vector rotate_vector(t_vector v, double angle)
{
  t_vector rotated;

  rotated.x = v.x * cos(angle) - v.y * sin(angle);
  rotated.y = v.x * sin(angle) + v.y * cos(angle);
  return (rotated);
}

void clear(t_data *data)
{
  int x;
  int y;

  x = 0;
  while (x < SCREEN_WIDTH)
  {
    y = 0;
    while (y < SCREEN_HEIGHT)
    {
      my_mlx_pixel_put(data, x, y, 0);
      y++;
    }
    x++;
  }
}

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

void rotate(t_master *master)
{
  if (master->keyboard.r_right)
  {
    master->render.dir = rotate_vector(master->render.dir, -ROTATE_SPEED);
    master->render.plane = rotate_vector(master->render.plane, -ROTATE_SPEED);
  }
  if (master->keyboard.r_left)
  {
    master->render.dir = rotate_vector(master->render.dir, ROTATE_SPEED);
    master->render.plane = rotate_vector(master->render.plane, ROTATE_SPEED);
  }
}

void move_x(t_master *master)
{
  if (master->keyboard.right)
  {
    double perpX = master->render.dir.y;
    double perpY = -master->render.dir.x;
    if (master->campus[(int)(master->render.pos.x + perpX * MOVE_SPEED)]
                      [(int)(master->render.pos.y)] != '1')
      master->render.pos.x += perpX * MOVE_SPEED;
    if (master->campus[(int)(master->render.pos.x)]
                      [(int)(master->render.pos.y + perpY * MOVE_SPEED)] != '1')
      master->render.pos.y += perpY * MOVE_SPEED;
  }
  if (master->keyboard.left)
  {
    double perpX = master->render.dir.y;
    double perpY = -master->render.dir.x;
    if (master->campus[(int)(master->render.pos.x - perpX * MOVE_SPEED)]
                      [(int)(master->render.pos.y)] != '1')
      master->render.pos.x -= perpX * MOVE_SPEED;
    if (master->campus[(int)(master->render.pos.x)]
                      [(int)(master->render.pos.y - perpY * MOVE_SPEED)] != '1')
      master->render.pos.y -= perpY * MOVE_SPEED;
  }
}

void move_y(t_master *master)
{
  if (master->keyboard.up)
  {
    if (master->campus[(int)(master->render.pos.x + master->render.dir.x * MOVE_SPEED)]
                      [(int)(master->render.pos.y)] != '1')
      master->render.pos.x += master->render.dir.x * MOVE_SPEED;
    if (master->campus[(int)(master->render.pos.x)]
                      [(int)(master->render.pos.y + master->render.dir.y * MOVE_SPEED)] != '1')
      master->render.pos.y += master->render.dir.y * MOVE_SPEED;
  }
  if (master->keyboard.down)
  {
    if (master->campus[(int)(master->render.pos.x - master->render.dir.x * MOVE_SPEED)]
                      [(int)(master->render.pos.y)] != '1')
      master->render.pos.x -= master->render.dir.x * MOVE_SPEED;
    if (master->campus[(int)(master->render.pos.x)]
                      [(int)(master->render.pos.y - master->render.dir.y * MOVE_SPEED)] != '1')
      master->render.pos.y -= master->render.dir.y * MOVE_SPEED;
  }
}

void move(t_master *master)
{
  move_x(master);
  move_y(master);
}

int controls(void *vars)
{
  t_master *master;
  t_keyboard keyboard;

  master = (t_master *)vars;
  keyboard = master->keyboard;
  (void)keyboard;
  rotate(master);
  move(master);
  renderization(&master->render, master, &master->img);
  mlx_put_image_to_window(master->render.mlx, master->render.win, master->img.img, 0, 0);
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
