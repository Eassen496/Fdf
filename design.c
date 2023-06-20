
#include "fdf.h"

static void	fdf_init(t_fdf *fdf)
{
	fdf->map.coordinate_z = 0;
	fdf->map.coordinate_y = 0;
	fdf->map.x_value = 1.00;
	fdf->map.angle_y = cos(M_PI / 3);
	fdf->map.angle_z = fdf->map.angle_y * sin(M_PI / 6);
	fdf->map.zoom = ceil((fdf->map.width > fdf->map.height)) \
		? (WIN_WIDTH / fdf->map.width) + 2 \
		: (WIN_HEIGHT / fdf->map.height) + 2;
}

static int	fdf_keys(int keycode, t_fdf *fdf)
{
	if (keycode == 0X35)
		exit(0);
	return (0);
}

int			fdf_main(char **argv)
{
	t_fdf	*fdf;

	if (!(fdf = (t_fdf *)malloc(sizeof(t_fdf))))
		ft_puterror("Memory Allocation failed! :O", 3);
	fdf->map.height = linecount(map);
	fdf->map.width = elem_count(map);
	fdf_read(argv[1], fdf);
	fdf_init(fdf);
	fdf->mlx.init = mlx_init();
	fdf->mlx.win = mlx_new_window(fdf->mlx.init, WIN_WIDTH, WIN_HEIGHT, &name[0][2]);
	mlx_hook(fdf->mlx.win, 2, 3, fdf_keys, fdf);
	mlx_loop_hook(fdf->mlx.init, fdf_draw, fdf);
	mlx_loop(fdf->mlx.init);
	return (0);
}
