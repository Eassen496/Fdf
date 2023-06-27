/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@marvin.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:11:17 by ale-roux          #+#    #+#             */
/*   Updated: 2023/02/25 16:11:18 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	wait_for_controls(t_fdf *fdf)
{
	mlx_hook(fdf->win_ptr, 2, 0, key_hook, fdf);
	mlx_hook(fdf->win_ptr, 4, 0, mouse_press, fdf);
	mlx_hook(fdf->win_ptr, 5, 0, mouse_release, fdf);
	mlx_hook(fdf->win_ptr, 6, 0, mouse_move, fdf);
}

void	keys_to_rotate(int key, t_fdf *fdf)
{
	if (key == KEY_1)
		fdf->alpha += 0.05;
	else if (key == KEY_2)
		fdf->alpha -= 0.05;
	else if (key == KEY_3)
		fdf->beta += 0.05;
	else if (key == KEY_4)
		fdf->beta -= 0.05;
	else if (key == KEY_5)
		fdf->gamma += 0.05;
	else if (key == KEY_6)
		fdf->gamma -= 0.05;
}

void	keys_to_shift(int key, t_fdf *fdf)
{
	if (key == UP)
		fdf->shift_y -= 10;
	else if (key == RIGHT)
		fdf->shift_x += 10;
	else if (key == DOWN)
		fdf->shift_y += 10;
	else if (key == LEFT)
		fdf->shift_x -= 10;
}

void	keys_for_projection(int key, t_fdf *fdf)
{
	if (key == I)
		fdf->projection = 1;
	else if (key == P)
		fdf->projection = 2;
}

int	key_hook(int key, t_fdf *fdf)
{
	if (key == ESC)
	{
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		exit(0);
	}
	else if (key >= KEY_1 && key <= KEY_5)
		keys_to_rotate(key, fdf);
	else if (key == GREATER_THAN && fdf->distance > 0.1)
		fdf->distance -= 0.1;
	else if (key == LESS_THAN && fdf->distance < 10)
		fdf->distance += 0.1;
	else if (key == I || key == P)
		keys_for_projection(key, fdf);
	else if (key >= LEFT && key <= UP)
		keys_to_shift(key, fdf);
	else if (key == KEY_MINUS && fdf->zoom > 1)
		fdf->zoom -= 1;
	else if (key == KEY_PLUS)
		fdf->zoom += 1;
	fdf->img = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel,
			&fdf->line_len, &fdf->endian);
	draw(fdf);
	return (0);
}
