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

void	make_min_max(t_fdf *fdf, int line, int i)
{
	if (fdf->altitude[line][i] < fdf->z_min)
		fdf->z_min = fdf->altitude[line][i];
	if (fdf->altitude[line][i] > fdf->z_max)
		fdf->z_max = fdf->altitude[line][i];
}

void	minus_lines(t_fdf *fdf)
{
	fdf->height = 0;
	fdf->z_min = 2147483647;
	fdf->z_max = -2147483648;
}

void	free_read_map(t_fdf *fdf, int count_line, char *line)
{
	free_int_mas(fdf->altitude, count_line);
	free_int_mas(fdf->color, count_line);
	free(fdf);
	free(line);
	perror("first split error");
	exit(-1);
}

void	free_read_fd(t_fdf *fdf)
{
	free(fdf);
	perror("Wrong FD");
	exit(-1);
}
