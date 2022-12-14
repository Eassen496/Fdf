
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

int	draw(mlx_t *mlx, mlx_image_t *g_img, int x, int y)
{

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

static int	wordcount(const char *s, char c, int opt, char **strs)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (opt == 1)
	{
		while (s[i])
		{
			while (s[i] && s[i] == c)
				i++;
			if (s[i] && s[i] != c)
				count++;
			while (s[i] && s[i] != c)
				i++;
		}
		return (count);
	}
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (1);
}

static int	wordlen(const char *s, char c, int i)
{
	int	i2;

	i2 = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		i2++;
	}
	return (i2);
}

static char	*putword(const char *str, char charset, int i)
{
	char	*rep;
	int		len;
	int		j;

	j = 0;
	if (!str)
		return (NULL);
	len = wordlen(str, charset, i);
	rep = malloc(sizeof(char) * (len + 1));
	if (!rep)
		return (NULL);
	while (str[i] && str[i] != charset)
	{
		rep[j] = str[i];
		j++;
		i++;
	}
	rep[j] = '\0';
	return (rep);
}

static char	**split2(const char *str, char charset, int j, int i)
{
	char	**rep;

	rep = NULL;
	rep = malloc(sizeof(char *) * (wordcount(str, charset, 1, rep) + 1));
	if (!rep)
		return (NULL);
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] == charset)
			i++;
		if (str[i] != '\0')
		{
			rep[j] = putword(str, charset, i);
			if (!rep[j++])
				if (wordcount(str, charset, 0, rep))
					return (NULL);
		}
		while (str[i] && str[i] != charset)
			i++;
	}
	rep[j] = 0;
	return (rep);
}

char	**ft_split(const char *str, char charset)
{
	char	**rep;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	rep = NULL;
	rep = split2(str, charset, j, i);
	if (!rep)
		return (NULL);
	return (rep);
}

int32_t	graphical_main(char *name, char *str)
{
	mlx_t	*mlx;
	char	**tab;

	tab = ft_split(str, '0');
    mlx = mlx_init(PIX_X, PIX_Y, name, true);
	if (!mlx)
        exit(EXIT_FAILURE);
    g_img = mlx_new_image(mlx, 1  , 1);
	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
	draw(mlx, g_img, 500, 500);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        graphical_main((char *)&argv[0][2], "0 0 0 0 10 0 0 2 5 1 0 0");
    }
    return (0);
}