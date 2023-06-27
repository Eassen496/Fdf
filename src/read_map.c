#include "fdf.h"

void	get_length(t_fdf *fdf, char *file_name)
{
	char	*line;
	int		fd;
	int		ret;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		free(fdf);
		perror("Wrong FD");
		exit(-1);
	}
	ret = get_next_line_1(fd, &line);
	if (ret == -1)
	{
		free(fdf);
		perror("couldn't read a line to get length");
		exit(-1);
	}
	fdf->length = count_words(line, ' ');
	free(line);
	close(fd);
}

int	is_map_valid(char **map_line, t_fdf *fdf, char **parts, int i)
{
	if (!parts)
	{
		free_parse_line(map_line, fdf, i);
		free_mas(parts);
		perror("invalid map");
		return (-1);
	}
	if (ft_isnumber(parts[0], 10) == 1)
	{
		free_parse_line(map_line, fdf, i);
		free_mas(parts);
		perror("non numeric map");
		return (-1);
	}
	if (parts[1] && (!ft_isnumber(parts[1], 16)
			|| ft_has_prefix(parts[1], 16) == 1))
	{
		free_parse_line(map_line, fdf, i);
		free_mas(parts);
		perror("color issue");
		return (-1);
	}
	return (0);
}

int	parse_line(char **map_line, t_fdf *fdf, int line)
{
	int		i;
	char	**parts;

	i = 0;
	while (map_line[i] && i <= fdf->length)
	{
		parts = ft_split(map_line[i], ',');
		if (is_map_valid(map_line, fdf, parts, i) == -1)
			return (-1);
		fdf->altitude[line][i] = ft_atoi(parts[0]);
		if (parts[1])
			fdf->color[line][i] = ft_atoi_base(parts[1], 16);
		else
			fdf->color[line][i] = -1;
		make_min_max(fdf, line, i);
		free_mas(parts);
		i++;
	}
	if (i != fdf->length)
	{
		free_parse_line(map_line, fdf, line);
		perror("invalid map");
		exit(-1);
	}
	return (0);
}

void	read_map(t_fdf *fdf, char *file_name)
{
	char	**map_line;
	int		fd;
	char	*line;
	int		count_line;

	get_length(fdf, file_name);
	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		free_read_fd(fdf);
	count_line = 0;
	minus_lines(fdf);
	while (get_next_line(fd, &line) == 1)
	{
		reallocate(fdf, count_line);
		map_line = ft_split(line, ' ');
		if (map_line == NULL)
			free_read_map(fdf, count_line, line);
		if (parse_line(map_line, fdf, count_line) == -1)
			free_after_parse(line, fd);
		free_mas(map_line);
		free(line);
		fdf->height++;
		count_line++;
	}
	close(fd);
}