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

void	free_mas(char **mas)
{
	int	i;

	if (mas)
	{
		i = 0;
		while (mas[i])
		{
			free(mas[i]);
			i++;
		}
		free(mas);
	}
}

void	free_int_mas(int **mas, int size)
{
	int	i;

	i = 0;
	if (mas[i])
	{
		while (i < size)
		{
			free(mas[i]);
			i++;
		}
		free(mas);
	}
}

void	free_parse_line(char **map_line, t_fdf *fdf, int i)
{
	free_mas(map_line);
	free_int_mas(fdf->altitude, i);
	free_int_mas(fdf->color, i);
	free(fdf);
}

void	free_after_parse(char *line, int fd)
{
	free(line);
	close(fd);
	exit(-1);
}
