/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:08:52 by ale-roux          #+#    #+#             */
/*   Updated: 2022/11/25 16:58:31 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <memory.h>
# define PIX_X 1920
# define PIX_Y 1080
# define BUFFER_SIZE 32

char			*get_next_line(int fd);
char			*ft_strchr(const char *s, int c);
void			*ft_calloc(unsigned int size);
int				ft_strlen(char *str);
char			*loadbuffer(char *str, int fd);
char			*saveclnr(char *str);
char			*lineclnr(char *str);
char			*freeall(char *s1, char *s2);
int32_t			graphical_main(char *name, char *str);
char            *ft_strjoin(char *s1, char *s2);
char            *ft_strrchr(const char *s, int c);
int             char_verif(char *str);
int             elem_count(char *str);
int             linecount(char *str);
int             elem_verif(char *str);
char            *verif_map(int fd);
void            help_printer(char *exec);
int             verif_extension(char *execname, char *filename);
void            arg_error(int argc);
int             isnl(char *str);
int             ft_strcmp(char *s1, char *s2);
int			    fdf_draw(t_fdf *fdf);
void		    fdf_read(char *argv, t_fdf *fdf);

typedef struct	s_mlx
{
	void	*init;
	void	*win;
	void	*img;
}				t_mlx;

typedef struct	s_image
{
	char	*data;
	int		size;
	int		endian;
	int		bpp;
}				t_image;

typedef struct	s_map
{
	int		**values;
	int		width;
	int		height;
	int		y0;
	int		y1;
	int		z0;
	int		z1;
	int		zoom;
	double	x_value;
	double	angle_y;
	double	angle_z;
}				t_map;

typedef struct	s_fdf
{
	t_mlx	mlx;
	t_map	map;
	t_image	image;
}				t_fdf;

#endif
