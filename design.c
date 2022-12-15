
#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define PIX_X 1920
#define PIX_Y 1080

mlx_image_t	*g_img;

char	*ft_strchr(const char *s, int c);

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
	int		count;
	float	j;
	float	deltay;

	while (str)
	{
		k = x + atoi(str);
		count = 0;
		mlx_image_to_window(mlx, g_img, x + atoi(str), y);
		j = ((x + atoi(ft_strchr(str, ' ')) + 50) - k) / 50;
		deltay = (y - (y + 25)) / 50;
		while (k < x + atoi(ft_strchr(str, ' ')) + 50)
		{
			k += j;
			y -= deltay;
			mlx_image_to_window(mlx, g_img, k, y);
		}
		mlx_image_to_window(mlx, g_img, k, y);
		str = ft_strchr(str, ' ');
	}
}

void	draw(mlx_t *mlx, mlx_image_t *g_img, char *str)
{
	int x;
	int	y;
	int i;

	i = 0;
	x = 1000;
	y = 250;
	if (str)
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
/*
int main(int argc, char **argv)
{
    if (argc == 2)
    {
        graphical_main((char *)&argv[0][2], "0 0 0 0 10 0 0 2 5 1 0 0");
    }
    return (0);
}
*/