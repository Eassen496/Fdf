#include "../header/fdf.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen((char *)s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

void	help_printer(char *exec)
{
	printf("===============================HELP");
	printf("===============================\n");
	printf("|| Name of program: %s\t\t\t\t\t||\n", (char *)&exec[2]);
	printf("|| launch program : %s <design.fdf>\t\t\t||\n", exec);
	printf("|| print help     : \"%s -h\" or \"%s --help\"\t\t||\n", exec, exec);
	printf("|| Control        :\t\t\t\t\t\t||\n");
	printf("||\t  - esc  : exit the program\t\t\t\t||\n");
	printf("=====================================");
	printf("=============================\n");
}

void	arg_error(int argc)
{
	if (argc == 1)
		printf("not enought arguments\n");
	else
		printf("too many arguments (%d but just 1 needed)\n", (argc - 1));
}