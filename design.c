
#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define PIX_X 1920
#define PIX_Y 1080

void	make_draw2(mlx_t *mlx, mlx_image_t *g_img, int x, float y);
void	make_draw3(mlx_t *mlx, mlx_image_t *g_img, int x, float y);

mlx_image_t	*g_img;

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
    {
        mlx_close_window(mlx);
        printf("Escaped pressed");
    }
}

void	make_draw1(mlx_t *mlx, mlx_image_t *g_img, int x, float y)
{
	int	pass;

	pass = 0;
	while (pass < 600)
	{
		mlx_image_to_window(mlx, g_img, x, y);
		x++;
		pass++;
		y = y + 0.5;
	}
}

void	make_draw4(mlx_t *mlx, mlx_image_t *g_img, int x, float y)
{
	int tmp;
	int pass;

	pass = 0;
	while (pass < 600)
	{	
		if ((tmp * 2) % 25 == 0)
			make_draw3(mlx, g_img, x, y);
		mlx_image_to_window(mlx, g_img, x, y);
		x++;
		y = y + 0.5;
		tmp = (int)y;
		pass++;
	}
	if ((tmp * 2) % 25 == 0)
			make_draw3(mlx, g_img, x, y);
}

void	make_draw3(mlx_t *mlx, mlx_image_t *g_img, int x, float y)
{
	int	pass;

	pass = 0;
	while (pass < 50)
	{
		mlx_image_to_window(mlx, g_img, x, y);
		x++;
		pass++;
		y = y - 0.5;
	}
}

void	make_draw2(mlx_t *mlx, mlx_image_t *g_img, int x, float y)
{
	int	pass;

	pass = 0;
	while (pass < 500)
	{
		if (x % 25 == 0)
			make_draw4(mlx, g_img, x, y);
		mlx_image_to_window(mlx, g_img, x, y);
		x++;
		pass++;
		y = y - 0.5;
	}
	printf("%d\n", pass);
}

int	ft_tablen(char *str)
{
	int i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			ret++;
		i++;
	}
	return (ret);
}

char	*next_int(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] <= '9' && str[i] >= '0')
			return (&str[i]);
		i++;
	}	
}

int	line_len(char *str)
{
	int i;
	int	ret;

	i = -1;
	ret = 1;
	while (str[++i])
	{
		if (str[i] <= '9' && str[i] >= '0')
		{
			ret++;
			while (str[i] <= '9' && str[i] >= '0')
				i++;
		}
	}
	return (ret);
}

int *line_creator(char *str)
{
	int			i;
	int 		tmp;
	static char *str2 = NULL;
	int			*tab;

	i = 0;
	if (!str2)
		ft_strcpy(str2, str);
	tab = malloc(line_len(str) * sizeof(int));
	while (str2 != '\n' && str2[i])
	{
		tab[i] = atoi(str2);
		i++;
		str2 = next_int(str);
	}
	return (tab);
}

int	**tab_creator(char *str)
{
	int	i;
	int tablen;
	int	elem;
	int	**tab;

	i = 0;
	tablen = ft_tablen(str);
	tab = malloc((tablen + 1) * sizeof(int *));
	while (i <= tablen)
	{
		tab[i] = line_creator(str);
		i++;
	}
	return (tab);
}

int32_t	graphical_main(char *name, char *str)
{
	mlx_t	*mlx;
	int		**tab;

	tab = tab_creator(str);
    mlx = mlx_init(PIX_X, PIX_Y, name, true);
	if (!mlx)
        exit(EXIT_FAILURE);
    g_img = mlx_new_image(mlx, 1  , 1);
	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
	make_draw1(mlx, g_img, 1000, 250);
	make_draw2(mlx, g_img, 500, 500);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{

    if (argc == 2)
    {
        graphical_main((char *)&argv[0][2]);
    }
    return (0);
}