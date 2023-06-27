/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@marvin.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:11:17 by ale-roux          #+#    #+#             */
/*   Updated: 2023/02/25 16:11:18 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_bresenham	*copy_coor_to_dots(t_draw *coor, t_bresenham *dots)
{
	dots->x = coor->x;
	dots->y = coor->y;
	dots->x1 = coor->x1;
	dots->y1 = coor->y1;
	return (dots);
}

void	free_init_window(t_fdf *fdf)
{
	free_int_mas(fdf->color, fdf->height);
	free_int_mas(fdf->altitude, fdf->height);
	free(fdf);
	exit(-1);
}

t_fdf	*init_window(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		free_init_window(fdf);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "FdF");
	if (!fdf->win_ptr)
		free_init_window(fdf);
	fdf->img = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
	if (!fdf->img)
		free_init_window(fdf);
	fdf->addr = mlx_get_data_addr(fdf->img,
			&fdf->bits_per_pixel, &fdf->line_len, &fdf->endian);
	if (!fdf->addr)
		free_init_window(fdf);
	fdf->zoom = minimum(WIDTH / fdf->length / 2, HEIGHT / fdf->height / 2);
	fdf->alpha = 0;
	fdf->beta = 0;
	fdf->gamma = 0;
	fdf->projection = 1;
	fdf->distance = 1;
	fdf->shift_x = 1;
	fdf->shift_y = 1;
	fdf->mouse = 1;
	return (fdf);
}
