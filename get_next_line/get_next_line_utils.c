/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 00:28:50 by ale-roux          #+#    #+#             */
/*   Updated: 2022/11/23 22:55:27 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strchr(const char *s, int c)
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

char	*gnl_strjoin(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	if (!s2)
		return (NULL);
	if (!s1)
		s1 = gnl_calloc(1);
	str = gnl_calloc((gnl_strlen(s1) + gnl_strlen(s2) + 1) * sizeof(char));
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

void	*gnl_calloc(unsigned int size)
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

size_t	gnl_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*freeall(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}
