/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-roux <ale-roux@marvin.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:11:17 by ale-roux          #+#    #+#             */
/*   Updated: 2023/02/25 16:11:18 by ale-roux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	maximum(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	minimum(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	module(int a)
{
	if (a < 0)
		return (-a);
	else
		return (a);
}

char	*cut_this_line(char *str, char c)
{
	char	*arr;
	int		i;
	int		j;
	int		size;

	i = 0;
	while (str[i] != c)
		i++;
	size = ft_strlen(str) - i;
	arr = (char *)malloc(sizeof(char) * (size + 1));
	i++;
	j = 0;
	while (i <= size)
	{
		arr[j] = str[i];
		j++;
		i++;
	}
	arr[j] = '\0';
	free(str);
	return (arr);
}

int	count_words(char *str, char c)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i + 1] == c || str[i + 1] == '\0') == 1
			&& (str[i] == c || str[i] == '\0') == 0)
			words++;
		i++;
	}
	return (words);
}
