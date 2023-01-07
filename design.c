/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:41:51 by ale-roux          #+#    #+#             */
/*   Updated: 2023/01/07 16:41:51 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define PIX_X 1920
#define PIX_Y 1080

mlx_image_t	*g_img;

char	*ft_strchr(const char *s, int c);
int		elem_count(char *str);
int		linecount(char *str);

char	*ft_strcpy(char *destination, char *source)
{
	int	i;

	i = 0;
	while (source[i])
	{
		destination[i] = source[i];
		i++;
	}
	destination[i] = '\0';
	return (destination);
}

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
    {
        mlx_close_window(mlx);
        printf("Escape pressed");
    }
}

void make_draw_x(int x, float y, char *str, mlx_t *mlx, mlx_image_t *g_img)
{
	float	k;
	float	j;
	float	deltay;
	int		count;
	int		lim;
	int		count2;

	count = 0;
	count2 = 0;
	lim = elem_count(str);
	while (count < lim)
	{
		k = x + atoi(str);
		mlx_image_to_window(mlx, g_img, k, y);
		j = ((x + atoi(strchr(str, ' ')) + 50) - k) / 50;
		deltay = (y - (y + 25)) / 50;
		while (k <= x + atoi(strchr(str, ' ')) + 50)
		{
			//printf("%f %d\n", k, x + atoi(strchr(str, ' ')) + 50);
			k += j;
			y -= deltay;
			count2++;
			mlx_image_to_window(mlx, g_img, k, y);
		}
		printf("%d\n", count2);
		x = k;
		if (str[0] == ' ')
			str = &str[1];
		str = strchr(str, ' ');
		count++;
	}
}

void	draw(mlx_t *mlx, mlx_image_t *g_img, char *str)
{
	int x;
	int	y;
	int i;
	int	end;

	i = 0;
	x = 750;
	y = 50;
	end = linecount(str);
	while (i < end)
	{
		make_draw_x(x, y, str, mlx, g_img);
		i++;
	}
}

int32_t	graphical_main(char *name, char *str)
{
	mlx_t	*mlx;

    mlx = mlx_init(PIX_X, PIX_Y, name, true);
	if (!mlx)
        exit(EXIT_FAILURE);
    g_img = mlx_new_image(mlx, 1  , 1);
	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
	draw(mlx, g_img, str);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}