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

void	free_fdf(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->height)
	{
		free(fdf->altitude[i]);
		i++;
	}
	free(fdf->altitude);
	i = 0;
	while (i < fdf->height)
	{
		free(fdf->color[i]);
		i++;
	}
	free(fdf->color);
}

void	project_1(t_bresenham *dots, t_fdf *fdf)
{
	dots->x1 *= fdf->zoom;
	dots->y1 *= fdf->zoom;
	dots->z1 *= fdf->zoom / fdf->distance;
	dots->x1 -= (fdf->length * fdf->zoom) / 2;
	dots->y1 -= (fdf->height * fdf->zoom) / 2;
	rotate_x(&dots->y1, &dots->z1, fdf->alpha);
	rotate_y(&dots->x1, &dots->z1, fdf->beta);
	rotate_z(&dots->x1, &dots->y1, fdf->gamma);
	if (fdf->projection == 1)
		iso_1(dots);
	dots->x1 += WIDTH / 2;
	dots->y1 += (HEIGHT + fdf->height * fdf->zoom) / 2;
	dots->x += fdf->shift_x;
	dots->x1 += fdf->shift_x;
	dots->y += fdf->shift_y;
	dots->y1 += fdf->shift_y;
}

t_bresenham	*project(t_bresenham *dots, t_fdf *fdf)
{
	dots->x *= fdf->zoom;
	dots->y *= fdf->zoom;
	dots->z *= fdf->zoom / fdf->distance;
	dots->x -= (fdf->length * fdf->zoom) / 2;
	dots->y -= (fdf->height * fdf->zoom) / 2;
	rotate_x(&dots->y, &dots->z, fdf->alpha);
	rotate_y(&dots->x, &dots->z, fdf->beta);
	rotate_z(&dots->x, &dots->y, fdf->gamma);
	if (fdf->projection == 1)
		iso(dots);
	dots->x += WIDTH / 2;
	dots->y += (HEIGHT + fdf->height * fdf->zoom) / 2;
	project_1(dots, fdf);
	return (dots);
}
