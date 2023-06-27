/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:52:35 by ale-roux          #+#    #+#             */
/*   Updated: 2022/11/23 23:06:28 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*lineclnr(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	if (!str[0])
		return (NULL);
	ret = gnl_calloc((isnl(str) + 2) * sizeof(char));
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
	ret = gnl_calloc((gnl_strlen(str) - i + 1) * sizeof(char));
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
		str = gnl_calloc(1);
	buffer = gnl_calloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
	{
		free(str);
		return (NULL);
	}
	readed = 1;
	while (!gnl_strchr(str, '\n') && readed != 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
			return (freeall(buffer, str));
		buffer[readed] = '\0';
		str = gnl_strjoin(str, buffer);
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
/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd = open("test", O_RDONLY);
	printf("fichier: %d", fd);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return (0);
}
*/
