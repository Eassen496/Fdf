/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:41:51 by ale-roux          #+#    #+#             */
/*   Updated: 2023/01/07 16:41:58 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 32

char			*get_next_line(int fd);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char *s1, char *s2);
void			*ft_calloc(unsigned int size);
int				ft_strlen(char *str);
char			*loadbuffer(char *str, int fd);
char			*saveclnr(char *str);
int				isnl(char *str);
char			*lineclnr(char *str);
char			*freeall(char *s1, char *s2);
int32_t			graphical_main(char *name, char *str);

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	if (!s2)
		return (NULL);
	if (!s1)
		s1 = ft_calloc(1);
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*freeall(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

void	*ft_calloc(unsigned int size)
{
	char			*ptr;
	unsigned int	i;

	i = 0;
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	while (i < size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}

char	*lineclnr(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	if (!str[0])
		return (NULL);
	ret = ft_calloc((isnl(str) + 2) * sizeof(char));
	if (!ret)
		return (NULL);
	while (str[i] && str[i] != '\n')
	{
		ret[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}

int	isnl(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*saveclnr(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = isnl(str);
	j = 0;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	ret = ft_calloc((ft_strlen(str) - i + 1) * sizeof(char));
	if (!ret)
	{
		free(str);
		return (NULL);
	}
	i++;
	while (str[i])
		ret[j++] = str[i++];
	free(str);
	return (ret);
}

char	*loadbuffer(char *str, int fd)
{
	char	*buffer;
	int		readed;

	if (!str)
		str = ft_calloc(1);
	buffer = ft_calloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		free(str);
		return (NULL);
	}
	readed = 1;
	while (!ft_strchr(str, '\n') && readed != 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
			return (freeall(buffer, str));
		buffer[readed] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*save = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = loadbuffer(save, fd);
	if (!save)
		return (NULL);
	line = lineclnr(save);
	save = saveclnr(save);
	return (line);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

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

	error = 0;
	line = 0;
	i = elem_count(str);
	while (line < linecount(str))
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

void	arg_error(int argc)
{
	if (argc == 1)
		printf("not enought arguments\n");
	else
		printf("too many arguments (%d but just 1 needed)\n", (argc - 1));
}

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
			graphical_main((char *)&argv[0][2], map);
		}
		return (0);
	}
	arg_error(argc);
	return (1);
}
