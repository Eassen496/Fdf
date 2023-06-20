/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:41:51 by ale-roux          #+#    #+#             */
/*   Updated: 2023/01/07 16:41:51 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/fdf.h"

int	main(int argc, char **argv)
{
	int		fd;
	int		verif;
	char	*map;

	if (argc == 2)
	{
		verif = verif_extension(argv[0], argv[1]);
		if (verif == 0)
		{
			fd = open(argv[1], O_RDONLY);
			if (fd <= 0)
			{
				printf("design doesn\'t exist\n");
				return (1);
			}
			map = verif_map(fd);
			if (!map)
				return (1);
			graphical_main(argv, map);
		}
		return (0);
	}
	arg_error(argc);
	return (1);
}
