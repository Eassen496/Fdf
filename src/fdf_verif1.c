#include "../header/fdf.h"

int	char_verif(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] >= '9' && str[i] <= '0' && str[i] != ' ')
			count++;
		i++;
	}
	if (count != 0)
		printf("invalid design (unknown char)");
	return (count);
}

int	elem_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[0] == '\n')
		i = 1;
	while (str[i] != '\n' && str[i] != '\0')
	{
		if (str[i] >= 48 && str[i] <= 57)
		{
			count++;
			while (str[i] >= 48 && str[i] <= 57)
			{
				i++;
			}
			i--;
		}
		i++;
	}
	return (count);
}

int	linecount(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (str[i])
	{
		if (str[i] == '\n')
			j++;
		i++;
	}
	return (j);
}

int	elem_verif(char *str)
{
	int	i;
	int	j;
	int	error;
	int	line;
	int	lim;

	error = 0;
	line = 0;
	i = elem_count(str);
	lim = linecount(str);
	while (line < lim)
	{
		j = elem_count(str);
		if (i != j)
		{
			error += 1;
			break ;
		}
		str = ft_strchr(str, '\n');
		line++;
	}
	if (error != 0)
		printf("invalid design (length line %d isn't correct)", line + 1);
	return (error);
}

char	*verif_map(int fd)
{
	int		verif;
	char	*str;
	char	*line;
	int		count;

	verif = 0;
	count = 0;
	str = ft_calloc(1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		str = ft_strjoin(str, line);
		line = get_next_line(fd);
		count++;
	}
	verif += char_verif(str);
	verif += elem_verif(str);
	if (verif != 0)
		return (NULL);
	return (str);
}