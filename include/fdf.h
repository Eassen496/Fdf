/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@marvin.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:11:17 by ale-roux          #+#    #+#             */
/*   Updated: 2023/02/25 16:11:18 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../minilibx_macos/mlx.h"

# define PURPLE	0x9A1F6A
# define PINK	0xC2294E
# define RED	0xEC3B00
# define ORANGE	0xEF8633
# define YELLOW	0xF3AF3D

# define WIDTH	1660
# define HEIGHT	1080

# define ESC 53
# define LEFT 123
# define RIGHT 124
# define DOWN 125
# define UP 126

# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define KEY_5 23
# define KEY_6 22
# define KEY_MINUS 27
# define KEY_PLUS 24
# define I 34
# define P 35
# define LESS_THAN 43
# define GREATER_THAN 47

# define LEFT_CLICK 1
# define SCROLL_UP 4
# define SCROLL_DOWN 5

typedef struct s_fdf
{
	int		buffer_size;
	void	*mlx_ptr;
	void	*win_ptr;
	int		**altitude;
	int		**color;

	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;

	int		length;
	int		height;
	int		z_min;
	int		z_max;

	float	alpha;
	float	beta;
	float	gamma;

	float	projection;
	float	distance;
	int		zoom;
	int		shift_x;
	int		shift_y;

	int		mouse;
	float	mouse_x;
	float	mouse_x1;
	float	mouse_y;
	float	mouse_y1;
}		t_fdf;

typedef struct s_draw
{
	int		x;
	int		y;
	int		x1;
	int		y1;
}		t_draw;

typedef struct s_util
{
	int		deltax;
	int		deltay;
	int		signx;
	int		signy;
	int		error;
	int		error2;
}		t_util;

typedef struct s_bresenham
{
	int		x;
	int		y;
	int		x1;
	int		y1;
	int		z;
	int		z1;
	int		x_step;
	int		y_step;
}		t_bresenham;

typedef struct s_gradient
{
	int		x;
	int		y;
	int		x1;
	int		y1;
	int		x_step;
	int		y_step;
}		t_gradient;

// color.c
double		percent(int start, int end, int current);
int			get_light(int start, int end, double percentage);
int			get_default_color(int z, t_fdf *fdf);
int			get_color(t_fdf *fdf, t_draw *coor);

// controls.c
void		wait_for_controls(t_fdf *fdf);
void		keys_to_rotate(int key, t_fdf *fdf);
void		keys_to_shift(int key, t_fdf *fdf);
void		keys_for_projection(int key, t_fdf *fdf);
int			key_hook(int key, t_fdf *fdf);

// mouse.c
void		zoom(int key, t_fdf *fdf);
int			mouse_move(int x, int y, void *param);
int			mouse_press(int key, int x, int y, void *param);
int			mouse_release(int key, int x, int y, void *param);

// copy.c
t_bresenham	*copy_coor_to_dots(t_draw *coor, t_bresenham *dots);
t_fdf		*init_window(t_fdf *fdf);
void		free_init_window(t_fdf *fdf);

// draw.c
void		put_pixel(t_fdf *fdf, int x, int y, int color);
void		bresenham(t_bresenham *dots, t_draw *coor, t_fdf *fdf);
t_bresenham	*mod_dots(t_bresenham *dots, t_draw *coor, t_fdf *fdf);
void		draw_horizontally(t_draw *coor, t_bresenham *dots, t_fdf *fdf);
void		draw(t_fdf *fdf);

// draw_utils.c
void		init_sign(t_bresenham *dots, t_util *a);
void		last_lines(t_bresenham *dots, t_draw *coor, t_fdf *fdf);

// fdf_utils.c
int			maximum(int a, int b);
int			minimum(int a, int b);
int			module(int a);
char		*cut_this_line(char *str, char c);
int			count_words(char *str, char c);

// projection.c
void		free_fdf(t_fdf *fdf);
void		project_1(t_bresenham *dots, t_fdf *fdf);
t_bresenham	*project(t_bresenham *dots, t_fdf *fdf);

// iso_and_rotate.c
void		iso(t_bresenham *dots);
void		iso_1(t_bresenham *dots);
void		rotate_x(int *y, int *z, float alpha);
void		rotate_y(int *x, int *z, float beta);
void		rotate_z(int *x, int *y, float gamma);

// reallocation.c
int			*try_memcpy(int *dst, int *src, size_t n);
int			*bbzero(int *s, size_t n);
int			**double_reallocation(int **old, int len, int count);
void		reallocate(t_fdf *fdf, int count_line);

// read_map_utils.c
void		make_min_max(t_fdf *fdf, int line, int i);
void		minus_lines(t_fdf *fdf);
void		free_read_map(t_fdf *fdf, int count_line, char *line);
void		free_read_fd(t_fdf *fdf);

// free.c
void		free_mas(char **mas);
void		free_int_mas(int **mas, int size);
void		free_parse_line(char **map_line, t_fdf *fdf, int i);
void		free_after_parse(char *line, int fd);

// read_map.c
int			is_map_valid(char **map_line, t_fdf *fdf, char **parts, int i);
void		get_length(t_fdf *fdf, char *file_name);
int			parse_line(char **map_line, t_fdf *fdf, int line);
void		read_map(t_fdf *fdf, char *file_name);

// utils.c
int			ft_isspace(int c);
int			ft_has_prefix(const char *str, int base);
int			ft_isnumber(char *str, int base);
int			ft_atoi_base(const char *str, int base);

#endif
