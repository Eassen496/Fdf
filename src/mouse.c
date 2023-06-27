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

void	zoom(int key, t_fdf *fdf)
{
	if (key == SCROLL_DOWN)
		fdf->zoom += 1;
	else if (key == SCROLL_UP && fdf->zoom > 1)
		fdf->zoom -= 1;
	fdf->img = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel,
			&fdf->line_len, &fdf->endian);
	draw(fdf);
}

int	mouse_move(int x, int y, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	fdf->mouse_x = fdf->mouse_x1;
	fdf->mouse_y = fdf->mouse_y1;
	fdf->mouse_x1 = x;
	fdf->mouse_y1 = y;
	if (fdf->mouse == 0)
	{
		fdf->beta += (x - fdf->mouse_x) * 0.002;
		fdf->alpha += (y - fdf->mouse_y) * 0.002;
		fdf->img = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
		fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel,
				&fdf->line_len, &fdf->endian);
		draw(fdf);
	}
	return (0);
}

int	mouse_press(int key, int x, int y, void *param)
{
	t_fdf	*fdf;

	(void)x;
	(void)y;
	fdf = (t_fdf *)param;
	if (key == SCROLL_UP || key == SCROLL_DOWN)
		zoom(key, fdf);
	else if (key == 1)
		fdf->mouse = 0;
	return (0);
}

int	mouse_release(int key, int x, int y, void *param)
{
	t_fdf	*fdf;

	(void)x;
	(void)y;
	(void)key;
	fdf = (t_fdf *)param;
	fdf->mouse = 1;
	return (0);
}
