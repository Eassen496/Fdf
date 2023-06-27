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

void	iso(t_bresenham *dots)
{
	int	previous_x;
	int	previous_y;

	previous_x = dots->x;
	previous_y = dots->y;
	dots->x = (previous_x - previous_y) * cos(0.523599);
	dots->y = -dots->z + (previous_x + previous_y) * sin(0.523599);
}

void	iso_1(t_bresenham *dots)
{
	int	previous_x1;
	int	previous_y1;

	previous_x1 = dots->x1;
	previous_y1 = dots->y1;
	dots->x1 = (previous_x1 - previous_y1) * cos(0.523599);
	dots->y1 = -dots->z1 + (previous_x1 + previous_y1) * sin(0.523599);
}

void	rotate_x(int *y, int *z, float alpha)
{
	int	previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

void	rotate_y(int *x, int *z, float beta)
{
	int	previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

void	rotate_z(int *x, int *y, float gamma)
{
	int	previous_x;
	int	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}
