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

int	*try_memcpy(int *dst, int *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	free(src);
	return (dst);
}

int	*bbzero(int *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		s[i] = 0;
		i++;
	}
	return (s);
}

int	**double_reallocation(int **old, int len, int count)
{
	int	i;
	int	**new;

	i = 0;
	new = (int **) malloc(sizeof (int *) * (count + 1));
	new[i] = (int *) malloc(sizeof (int) * len);
	new[i] = bbzero(new[i], len);
	while (i < count)
	{
		new[i] = try_memcpy(new[i], old[i], len);
		i++;
		new[i] = (int *) malloc(sizeof (int) * len);
		new[i] = bbzero(new[i], len);
	}
	if (count > 0)
		free(old);
	return (new);
}

void	reallocate(t_fdf *fdf, int count_line)
{
	fdf->altitude = double_reallocation(fdf->altitude, fdf->length, count_line);
	fdf->color = double_reallocation(fdf->color, fdf->length, count_line);
	if (!(fdf->altitude) || !(fdf->color))
	{
		free_int_mas(fdf->altitude, count_line);
		free_int_mas(fdf->color, count_line);
		free(fdf);
		perror("malloc error");
		exit(-1);
	}
}
