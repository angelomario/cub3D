/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <aquissan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:31:28 by aquissan          #+#    #+#             */
/*   Updated: 2025/02/27 17:51:00 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdbool.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
# define PI 3.14
// # define ROTATE_SPEED 0.008
# define SPEED 0.010
# define ESC 65307
# define RRIGHT 65363
# define RUP 65362
# define RDOWN 65364
# define RLEFT 65361
# define UP 119
# define LEFT 97
# define RIGHT 100
# define DOWN 115


typedef struct s_map
{
	char			*line;
	struct s_map	*next;
}					t_map;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_intvector
{
	int	x;
	int	y;
}	t_intvector;

typedef struct s_graph
{
	double			posX;
	double			posY;
	double			dirX;
	double			dirY;
	double			planeX;
	double			planeY;
}					t_graph;


typedef	struct s_keyboard
{
	bool right;
	bool left;
	bool down;
	bool up;
	bool r_right;
	bool r_left;
	bool r_down;
	bool r_up;
}	t_keyboard;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;


	void    *textures[4];
    char    *tex_addr[4];
	char	*tex_paths[4];
    int     tex_width[4];
    int     tex_height[4];

	int		tex_endian[4];
	int		tex_line_length[4];
	int		tex_bits_per_pixel[4];
}				t_data;

typedef struct s_minilib
{
	void* mlx;
	void* win;
	void* img;
	t_vector pos;
	t_vector dir;
	t_vector plane;
	t_vector deltaDist;
	t_vector distToSide;
	t_intvector mapPos;
	int wallHeight;
	double perpendicularDist;
	t_vector rayDir;
}	t_minilib;


typedef struct s_master
{
	int				wrongmap;
	int				C;
	int				F;
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	char			**campus;
	t_minilib		render;
	t_data 			img;
	t_keyboard		keyboard;
}					t_master;

typedef struct s_texture
{
	int				index;
	int				x;
	int				y;
	double			step;
	double			pos;
	unsigned int	color;
}           		t_texture;


// FUNCTIONS
t_map				*ft_read_file(char *filepath);
t_master			*get_master(t_map *map);
int					getcolor(char *str, t_master *mastr);
void 				renderization(t_minilib *render, t_master *master, t_data *img);
void				draw_texture(int hitSide, t_intvector *pos, t_data *img, t_master *master);
void 				clear(t_data *data);
t_minilib 			set_cardial(t_master *master);
void				dda(t_master *master, t_minilib *render, int *hitSide, t_intvector *step, t_intvector *wallMapPos);
t_vector 			set_distToSide(t_intvector *step, t_vector rayDir, t_minilib *render, t_intvector mapPos);
t_vector 			setDeltaDist(t_vector rayDir);
void 				setWallHeight(t_minilib *render, int hitSide, t_intvector wallMapPos, t_intvector step);
void				rotate(t_master *master);
void				move_x(t_master *master);
void				move_y(t_master *master);
void				move(t_master *master);
int					controls(void *vars);
t_vector 			rotate_vector(t_vector v, double angle);
t_vector 			get_player_pos(char **campus);

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
void 				show_map(char **map);
void				 my_mlx_pixel_put(t_data *data, int x, int y, int color);

// FREEZE
void				ft_free_stack(t_map *map);
void				ft_free_master(t_master *master);
int					ft_freematriz(char **mat);
void 				clear(t_data *data);

#endif