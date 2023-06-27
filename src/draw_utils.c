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

void	init_sign(t_bresenham *dots, t_util *a)
{
	if (dots->x < dots->x1)
		a->signx = 1;
	else
		a->signx = -1;
	if (dots->y < dots->y1)
		a->signy = 1;
	else
		a->signy = -1;
}

void	last_lines(t_bresenham *dots, t_draw *coor, t_fdf *fdf)
{
	coor->y = 0;
	coor->y1 = 1;
	coor->x = fdf->length - 1;
	coor->x1 = fdf->length - 1;
	while (coor->y1 < fdf->height)
	{
		bresenham(mod_dots(dots, coor, fdf), coor, fdf);
		coor->y += 1;
		coor->y1 += 1;
	}
	coor->x = 0;
	coor->x1 = 1;
	coor->y = fdf->height - 1;
	coor->y1 = fdf->height - 1;
	while (coor->x1 < fdf->length)
	{
		bresenham(mod_dots(dots, coor, fdf), coor, fdf);
		coor->x += 1;
		coor->x1 += 1;
	}
}
