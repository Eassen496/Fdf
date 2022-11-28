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
int			    ft_strlen(char *str);
char			*loadbuffer(char *str, int fd);
char			*saveclnr(char *str);
int				isnl(char *str);
char			*lineclnr(char *str);
char			*freeall(char *s1, char *s2);

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
	return (0);
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

int ft_strlen(char *str)
{
    int i;

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

int personnage_verif(char *str)
{
    int personnage;
    int i;

    i = 0;
    personnage = 0;
    while (str[i])
    {
        if (str[i] == 'P')
            personnage++;
        i++;
    }
    if (personnage == 0)
    {
        printf("invalid map (0 personnage)\n");
        return (1);
    }
    else if (personnage != 1)
    {
        printf("invalid map (too many personnages)\n");
        return (1);
    }
    return (0);
}

int exit_verif(char *str)
{
    int exit;
    int i;

    i = 0;
    exit = 0;
    while (str[i])
    {
        if (str[i] == 'E')
            exit++;
        i++;
    }
    if (exit == 0)
    {
        printf("invalid map (0 exit)\n");
        return (1);
    }
    else if (exit != 1)
    {
        printf("invalid map (too many exit)\n");
        return (1);
    }
    return (0);
}

int collectible_verif(char *str)
{
    int collectible;
    int i;

    i = 0;
    collectible = 0;
    while (str[i])
    {
        if (str[i] == 'C')
            collectible++;
        i++;
    }
    if (collectible == 0)
    {
        printf("invalid map (0 collectible)\n");
        return (1);
    }
    return (0);
}

int lenmap(char *str)
{
    int i;
    int count;
    int j;
    int count2;

    i = 0;
    j = ft_strlen(str);
    count = 0;
    count2 = 0;
    while (str[i] != '\n')
    {
        if (str[i] == '1')
            count++;
        i++;
    }
    while (str[j] != '\n')
    {
        if (str[j] == '1')
            count2++;
        j--;
    }
    if (i != count || i != count2)
        return (-1);
    return (count);
}

int middlenmap(char *str)
{
    int i;
    int count;
    int nl;

    i = 0;
    count = 0;
    nl = 0;
    while (str[i])
    {
        if (str[i] == '\n')
        {
            if (str[i - 1] == '1' && str[i + 1] == '1')
                count++;
            nl++;
        }
        i++;
    }
    if (nl != count)
        return (-1);
    return (count);
}

int wall_verif(char *str)
{
    int wall;
    int i;
    int width;
    int height;

    i = 0;
    wall = 0;
    width = lenmap(str);
    height = middlenmap(str);
    if (width == -1 || height == -1)
    {
        printf("invalid map (map not closed)\n");
        return (1);
    }
    return (0);
}

int char_verif(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] != 'C' && str[i] != 'P' && str[i] != 'E' && str[i] != '0' 
                && str[i] != '1' && str[i] != '\n')
                count++;
        i++;
    }
    if (count != 0)
        printf("invalid map (unknown char)");
    return (count);
}

int playable_map(int i, int j, char *str)
{
    int ret;
    int boolean;

    ret = 1;
    boolean = 1;
    while (boolean != 0)
    {
        if (str[j + 1] == '0')
            j = j + 1;
        else if (str[j - 1] == '0')
            j = j - 1;
        else if (str[j - i] == '0')
            j = j - i;
        else if (str[j + i] == '0')
            j = j + i;
        else
            boolean = 0;
        ret = 0;
    }
    return (ret);
}

int playable_map_verif(char *str)
{
    int i;
    int j;
    int error;

    i = 0;
    error = 0;
    while (str[i] == '1')
        i++;
    j = 0;
    while (str[j] != 'P')
       j++;
    error = playable_map(i, j, str);
    if (error != 0)
        printf("invalid map (map is not finnishable)");
    return (error);
}

char *verif_map(int fd)
{
    int     verif;
    char    *str;
    char    *line;

    verif = 0;
    str = ft_calloc(1);
    line = get_next_line(fd);
    while (line != NULL)
    {
        str = ft_strjoin(str, line);
        line = get_next_line(fd);
    }
    verif += exit_verif(str);
    verif += personnage_verif(str);
    verif += collectible_verif(str);
    verif += wall_verif(str);
    verif += char_verif(str);
    verif += playable_map_verif(str);
    if (verif != 0)
        return (NULL);
    return (str);
}

int verif_extension(char *filename)
{
    char *extension;
    int verif;

    extension = ".fdf";
    verif = ft_strcmp(ft_strrchr(filename, '.'), extension);
    if (verif == 0)
        return (0);
    else
    {
        printf("bad file extension\n");
        return (1);
    }
}

int main(int argc, char **argv)
{
    int     fd;
    int     verif;
    char    *map;

    if (argc == 2)
    {
        verif = verif_extension(argv[1]);
        if (verif == 0)
        {
            fd = open(argv[1], O_RDONLY);
            if (fd <= 0)
            {
                printf("map doesn\'t exist\n");
                return (1);
            }
            map = verif_map(fd);
            if (!map)
                return (1);
            //graphical_main(map);
        }
        return (0);
    }
    printf("missing arguments or too many\n");
    return (1);
}