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

void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	int		i;

	if (x < WIDTH && x >= 0 && y >= 0 && y < HEIGHT)
	{
		i = (x * fdf->bits_per_pixel / 8) + (y * fdf->line_len);
		fdf->addr[i] = color;
		fdf->addr[++i] = color >> 8;
		fdf->addr[++i] = color >> 16;
	}
}

void	bresenham(t_bresenham *dots, t_draw *coor, t_fdf *fdf)
{
	t_util		a;

	a.deltax = module(dots->x1 - dots->x);
	a.deltay = module(dots->y1 - dots->y);
	init_sign(dots, &a);
	a.error = a.deltax - a.deltay;
	while (dots->x != dots->x1 || dots->y != dots->y1)
	{
		put_pixel(fdf, dots->x, dots->y, get_color(fdf, coor));
		a.error2 = a.error * 2;
		if (a.error2 > -a.deltay)
		{
			a.error -= a.deltay;
			dots->x += a.signx;
		}
		if (a.error2 < a.deltax)
		{
			a.error += a.deltax;
			dots->y += a.signy;
		}
	}
}

t_bresenham	*mod_dots(t_bresenham *dots, t_draw *coor, t_fdf *fdf)
{
	dots = copy_coor_to_dots(coor, dots);
	dots->z = fdf->altitude[coor->y][coor->x];
	dots->z1 = fdf->altitude[coor->y1][coor->x1];
	dots = project(dots, fdf);
	return (dots);
}

void	draw_horizontally(t_draw *coor, t_bresenham *dots, t_fdf *fdf)
{
	coor->x1 = coor->x + 1;
	bresenham(mod_dots(dots, coor, fdf), coor, fdf);
	coor->x1 = coor->x;
	coor->y1 = coor->y + 1;
	bresenham(mod_dots(dots, coor, fdf), coor, fdf);
	coor->y1 = coor->y;
	coor->x++;
}

void	draw(t_fdf *fdf)
{
	t_draw		*coor;
	t_bresenham	*dots;

	coor = (t_draw *)malloc(sizeof(t_draw));
	dots = (t_bresenham *)malloc(sizeof(t_bresenham));
	coor->y = 0;
	while (coor->y < fdf->height - 1)
	{
		coor->x = 0;
		coor->y1 = coor->y;
		while (coor->x < fdf->length - 1)
			draw_horizontally(coor, dots, fdf);
		coor->y++;
	}
	last_lines(dots, coor, fdf);
	free(coor);
	free(dots);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img, 0, 0);
}
