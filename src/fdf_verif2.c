#include "../header/fdf.h"

int	verif_extension(char *execname, char *filename)
{
	char	*extension;
	int		verif;

	extension = ".fdf";
	verif = ft_strcmp(ft_strrchr(filename, '.'), extension);
	if (verif == 0)
		return (0);
	else if (ft_strcmp(filename, "--help") == 0
		|| ft_strcmp(filename, "-h") == 0)
		help_printer(execname);
	else if (ft_strrchr(filename, '.') == NULL)
		printf("Error ! no extension given");
	else
		printf("Error ! bad file extension\n");
	return (1);
}