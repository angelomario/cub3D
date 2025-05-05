/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:55:53 by aquissan          #+#    #+#             */
/*   Updated: 2025/05/05 16:32:37 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
# define BLOCK "█"
# define READ O_RDONLY
# define WRITE O_WRONLY
# define QTD_TEXTURE 174
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"
# include <bass.h>
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <string.h>

# if !defined SCREEN_WIDTH
#  define SCREEN_WIDTH 800
# endif
# if !defined SCREEN_HEIGHT
#  define SCREEN_HEIGHT 600
# endif
# if !defined SPEED
#  define SPEED 0.010
# endif
# if !defined PIXEL_SIZE
#  define PIXEL_SIZE 10
# endif
# define PI 3.14
# define ROTATE_SPEED 500
# define LIMIT_HIGH_VIEW 400
# define ESC 65307
# define RRIGHT 65363
# define RUP 65362
# define RDOWN 65364
# define RLEFT 65361
# define UP 119
# define LEFT 97
# define RIGHT 100
# define DOWN 115
# define WEAPON_TYPES 6
# define ACTION_TYPES 3
# define IMAGE_COUNT 14
# define ONE 49
# define TWO 50
# define THREE 51
# define FOUR 52
# define FIVE 53
# define SIX 54
# define SEVEN 55
# define EIGHT 56
# define SZERO 65438
# define LCTRL 65508
# define OPENDOR 101
# define SPACE 32
# define ENTER 65293
# define CTRL 65507

# define FIRE 0
# define WALK 1
# define STOP 2

// STOP FIRE WALK

typedef struct s_map
{
	char			*line;
	struct s_map	*next;
}					t_map;

typedef struct s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_intvector
{
	int				x;
	int				y;
}					t_intvector;

typedef struct s_floor_vars
{
	int				p;
	t_vector		floor;
	t_intvector		tex;
	t_vector		left_ray;
	t_vector		right_ray;
	double			camera_factor;
	double			row_distance;
}					t_floor_var;

typedef struct s_ceil_var
{
	t_intvector		sky;
	int				color;
	double			angle;
	double			v_offset;
	char			*pixel;
}					t_ceil_var;

typedef struct s_keyboard
{
	bool			right;
	bool			left;
	bool			down;
	bool			up;
	bool			open_door;
	bool			close_door;
	bool			r_right;
	bool			r_left;
	bool			r_down;
	bool			r_up;
	bool			mouse_left;
	bool			mouse_right;
}					t_keyboard;

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;

	void			*textures[4];
	char			*tex_addr[4];
	char			*tex_paths[4];
	int				tex_width[4];
	int				tex_height[4];
	int				tex_endian[4];
	int				tex_line_length[4];
	int				tex_bits_per_pixel[4];

	void			*player_texture[5][3][13];
	char			*player_texture_addr[5][3][13];
	char			*player_texture_paths[5][3][13];
	int				player_texture_width[5][3][13];
	int				player_texture_height[5][3][13];
	int				player_texture_endian[5][3][13];
	int				player_texture_line_length[5][3][13];
	int				player_texture_bits_per_pixel[5][3][13];

	void			*door_texture[3][13];
	char			*door_texture_addr[3][13];
	char			*door_texture_paths[3][13];
	int				door_texture_width[3][13];
	int				door_texture_height[3][13];
	int				door_texture_endian[3][13];
	int				door_texture_line_length[3][13];
	int				door_texture_bits_per_pixel[3][13];

	void			*ceil_texture;
	char			*ceil_texture_addr;
	char			*ceil_texture_paths;
	int				ceil_texture_width;
	int				ceil_texture_height;
	int				ceil_texture_endian;
	int				ceil_texture_line_length;
	int				ceil_texture_bits_per_pixel;

	void			*floor_texture;
	char			*floor_texture_addr;
	char			*floor_texture_paths;
	int				floor_texture_width;
	int				floor_texture_height;
	int				floor_texture_endian;
	int				floor_texture_line_length;
	int				floor_texture_bits_per_pixel;
	int				texture_step;
}					t_data;

typedef struct s_image
{
	void			*img;
	char			*path;
	char			*addr;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_image;

typedef struct s_preload
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;

	t_image			background;
	t_image			logo[13];
}					t_preload;

typedef struct s_minilib
{
	void			*mlx;
	void			*win;
	void			*img;
	t_vector		pos;
	t_vector		dir;
	t_vector		plane;
	t_vector		deltadist;
	t_vector		disttoside;
	t_intvector		mappos;
	int				wallheight;
	double			perpendiculardist;
	t_vector		raydir;

	bool			is_door;
	int				door_height;
	t_intvector		door_map_pos;
	char			door_object_touched;
}					t_minilib;

typedef struct s_3d
{
	int				m;
	int				l;
	int				c;
}					t_3d;

typedef struct s_sound
{
	HSTREAM			background;
	HSTREAM			run;
	HSTREAM			pistol;
	HSTREAM			shotgun;
	HSTREAM			shotgun_frst;
	HSTREAM			revolver_3;
	HSTREAM			revolver;
	HSTREAM			door_open;
	HSTREAM			door_close;
}					t_sound;

typedef struct s_master
{
	int				wrongmap;
	int				c;
	int				f;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			**campus;
	t_minilib		render;
	t_data			img;
	t_keyboard		keyboard;
	t_intvector		wallmappos;
	int				view_high;
	t_3d			dimension;
	int				time_animation;
	int				limit_time_animation;

	int				index_door;
	int				type_door;
	int				wall_hitside;
	int				door_hitside;
	int				door_time_animation;
	int				door_limit_time_animation;
	t_intvector		focused_open_door;
	t_intvector		focused_close_door;
	int				wait_to_close_the_door;

	t_list			*data_door;
	t_list			*data_root_door;
	double			rotate_angle;
	BOOL			bass_active;
	HSTREAM			weapon;
	t_sound			sounds;
	BOOL			game_started;
	t_preload		preload;
}					t_master;

typedef struct s_texture
{
	int				index;
	int				x;
	int				y;
	double			step;
	double			pos;
	unsigned int	color;
}					t_texture;

typedef struct s_area
{
	int				ini_x;
	int				ini_y;
	int				end_x;
	int				end_y;
}					t_area;

typedef struct s_size
{
	int				width;
	int				height;
}					t_size;

typedef struct s_bresenham
{
	int				x_ini;
	int				y_ini;
	int				x_end;
	int				y_end;
	int				inc_x;
	int				inc_y;
	int				dx;
	int				dy;
	int				x;
	int				y;
}					t_bresenham;

typedef struct s_texture_player
{
	float			scale;
	int				color;
	int				orig_width;
	int				orig_height;
	int				new_width;
	int				new_height;
	int				start_x;
	int				start_y;
	int				src_x;
	int				src_y;
}					t_texture_player;

typedef struct s_draw_door
{
	int				start_door;
	int				end_door;
	t_texture		texture_door;
}					t_draw_door;

typedef struct s_door_data
{
	int				door_height;
	int				door_hitside;
	t_intvector		door_map_pos;
	double			perpendicular_dist_door;
}					t_door_data;

typedef char		*t_texture_paths[6][3][14];

// FUNCTIONS
t_map				*ft_read_file(char *filepath);
t_master			*get_master(t_map *map);
int					getcolor(char *str, t_master *mastr);
void				renderization(t_minilib *render, t_master *master,
						t_data *img);
void				draw_texture(t_intvector *pos, t_data *img,
						t_master *master);
void				clear(t_data *data);
t_minilib			set_cardial(t_master *master);
void				dda(t_master *master, t_intvector *step,
						t_intvector *wallMapPos);
t_vector			set_disttoside(t_intvector *step, t_vector raydir,
						t_minilib *render, t_intvector mapPos);
t_vector			setdeltadist(t_vector raydir);
void				setwallheight(t_minilib *render, t_master *master,
						t_intvector step);
void				rotate(t_master *master);
void				move_x(t_master *master);
void				move_y(t_master *master);
int					controls(void *vars);
t_vector			rotate_vector(t_vector v, double angle);
t_vector			get_player_pos(char **campus);

// CHECK MAP
int					check_filename(char *filename);
int					check_components(char *line, t_master *master);
int					have_valid_wall(char **map);
int					ft_find_leak(char **tab);
int					ft_orizontalwall(char **line);
int					check_around(char **map, int x, int y);
int					around_character(char **tab, t_master *master);

// UTILS
int					is_there_something_wrong(t_master *master, t_map *map);
int					ft_countmatriz(char **mat);
int					initializedefault(t_master *master);
int					ft_countlinecampus(t_map *list);
void				ft_replacechar(char *str, char to_find, char to_replace);
int					ft_replacestr(char **str, char *to_replace);
int					is_voidline(char *line);
int					ft_countline(char **map);
int					count_var(char **map, char var);
void				show_map(char **map);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
int					printerror(char *str);
void				msg_error_image_not_found(int i, void *mlx, t_data *img);
int					load_textures(void *mlx, t_data *img, t_master *master);
unsigned int		get_color(int hitSide, t_texture *texture, t_data *img);
int					get_texture_index(int hitSide, t_vector rayDir);
int					get_draw_end_position(int wallheight, t_master *master);
int					get_draw_start_position(int wallheight, t_master *master);
void				draw_floor(t_intvector *pos, t_data *img, t_master *master);
void				draw_ceiling(int drawStart, t_intvector *pos, t_data *img,
						t_master *master);
int					get_x_coordinate_texture(int index_img, int hitSide,
						t_master *master, t_data *img);
int					wait_hooks(t_master *master);
int					check_door(char **campus);

// HOOKS
int					key_release(int keycode, t_master *master);
int					key_hook(int keycode, t_master *master);
int					key_exit(t_master *master);
int					key_exit_2(t_master *master);
int					mousemove(int x, int y, t_master *master);

// FREEZE
void				ft_free_stack(t_map *map);
void				ft_free_master(t_master *master);
int					ft_freematriz(char **mat);
void				clear(t_data *data);
int					free_textures(void *mlx, t_data *img);
int					free_player_texture(void *mlx, t_data *img);

// SET SMALL AREA VALUE
int					get_height_player_line(t_master *master);
int					get_width_player_line(t_master *master);
void				draw_small_map(t_master *master);
void				set_area_value(t_master *master, t_size *size, t_area *area,
						t_area *extra);
void				adjust_initial_area_values(t_master *master, t_area *area,
						t_area *extra);
void				adjust_final_area_values(t_master *master, t_area *area,
						t_area *extra);
void				draw_map_util(t_master *master, t_vector pos, int i1,
						int i2);

// DRAW SMALL MAP
void				init_bresenham(t_bresenham *bresenham);
void				draw_big_pixel(t_master *master, int size, t_vector pos,
						int color);
void				draw_positive_straight_line(t_master *master,
						t_bresenham *bresenham, int size, int color);
void				draw_negative_straight_line(t_master *master,
						t_bresenham *bresenham, int size, int color);
void				draw_straight_line(t_master *master, t_bresenham *line,
						int size, int color);

// DRAW PLAYER
char				**escopeta_dupla(void);
char				**escopeta(void);
char				**pistola(void);
char				**lupara(void);
char				**mgun(void);
int					load_player_texture(void *mlx, t_data *img);

void				init_data_struct(t_data *data);
void				draw_player(t_master *master);
int					get_image_quantity_by_weapon_type(int index);
int					load_all_texteres(void *mlx, t_data *img, t_master *master);
void				draw_crosshair(t_master *master);
void				player_animation(t_master *master);

void				shotgun_texture_set(t_texture_player *texture_player,
						t_master *master);
void				lupara_texture_setting(t_texture_player *texture_player,
						t_master *master);
void				mgun_texture_setting(t_texture_player *texture_player,
						t_master *master);
void				shotgun_dub_texture_set(t_texture_player *texture_player,
						t_master *master);
void				pistola_texture_setting(t_texture_player *texture_player,
						t_master *master);

// DRAW DOOR

char				**grade_de_cela(void);
char				**porta_de_dilatacao(void);
char				**porta_de_madeira(void);
int					load_door_texture(void *mlx, t_data *img);
void				free_door_texture(void *mlx, t_data *img);
int					get_image_quantity_by_door_type(int index);

void				draw_door(t_intvector *pos, t_data *img, t_master *master);
void				door_dda(t_master *master, t_intvector *step,
						t_intvector *wallMapPos);
void				set_door_height(t_minilib *render, t_master *master,
						t_intvector step);

void				wall_and_door_dda(t_master *master, t_intvector *step);
void				set_wall_and_door_height(t_master *master,
						t_minilib *render, t_intvector step);
void				draw_texture_and_door(t_intvector *pos, t_data *img,
						t_master *master);
void				draw_skybox(int drawStart, t_intvector *pos, t_data *img,
						t_master *master);
void				draw_floor(t_intvector *pos, t_data *img, t_master *master);

int					get_image_quantity_by_door_type(int index);
bool				player_near_the_door(t_master *master);

char				*door_one_character_list(void);
char				*door_two_character_list(void);
char				*door_three_character_list(void);
int					get_image_index_by_character_type(t_master *master);
bool				door_found(t_master *master, t_intvector pos);

void				animation_open_the_door(t_master *master);
void				animation_close_the_door(t_master *master);

bool				valid_character_pass(char chr, t_master *master);
t_intvector			get_pos_door(t_master *master);

bool				four_doors(t_master *master);
bool				three_doors(t_master *master);
bool				two_doors(t_master *master);
bool				more_than_one_door(t_master *master);
t_intvector			get_pos_door_is_in_front_of_the_player(t_master *master);
t_intvector			get_pos_door_around_the_player(t_master *master);

void				init_door_data(t_door_data *data);
void				free_door_data(void *data);
int					sound_init(t_sound *sounds, BOOL *bass);
int					play_sound(HSTREAM sound, int vol);
int					set_weapon(t_master *master, int index);
int					clear_sounds(t_sound sounds, BOOL bass);
int					free_preload(t_preload *preload, void *mlx);
int					preload(t_master *master);
int					set_preload_default(t_preload *preload);
int					set_preload_image(t_preload *pl, void *mlx);
int					loading(void);
#endif
