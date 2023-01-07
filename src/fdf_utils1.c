#include "../header/fdf.h"

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
