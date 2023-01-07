#include "../header/fdf.h"

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