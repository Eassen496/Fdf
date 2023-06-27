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

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (write(2, "Allocation failed\n", 18));
	if (argc != 2)
	{
		free(fdf);
		return (write(2, "Wrong argument\n", 15));
	}
	read_map(fdf, argv[1]);
	fdf = init_window(fdf);
	draw(fdf);
	wait_for_controls(fdf);
	mlx_loop(fdf->mlx_ptr);
	free_init_window(fdf);
	return (0);
}
