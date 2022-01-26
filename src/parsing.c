#include <stdio.h>
#include "FdF.h"

t_point	*new_point(float x, float y, float z)
{
	t_point	*result;

	result = malloc(sizeof(t_point));
	if (! result)
		return (NULL);
	result->x = x;
	result->y = y;
	result->z = z;
	return (result);
}

void	*free_map(t_map **map)
{
	free_2d_array((void **)(*map)->grid);
	free(*map);
	*map = NULL;
	return (NULL);
}

void	set_point(t_point *pt, double x, double y, double z)
{
	pt->x = x;
	pt->y = y;
	pt->z = z;
}

t_map	*new_map(int width, int height)
{
	t_map	*result;

	result = malloc(sizeof(t_map));
	if (! result)
		return (NULL);
	result->grid = malloc((width + 1) * sizeof (t_point *));
	if (! result->grid)
		return (NULL);
	result->grid[width] = NULL;
	result->width = width;
	result->height = height;
	while (width--)
	{
		result->grid[width] = malloc((height) * sizeof(t_point));
		if (! result->grid[width])
			return (free_map(&result));
	}
	return (result);
}

int parse_line(char *line, t_map *map, int y_act)
{
	char	**split_line;
	int		x_act;

	x_act = 0;
	split_line = ft_split(line, ' ');
	if (! split_line)
		return (1);
	while (split_line[x_act])
	{
		set_point(&map->grid[x_act][y_act], \
		x_act, y_act, ft_atoi(split_line[x_act]));
		x_act++;
	}
	free_2d_array((void **) split_line);
	return (0);
}
//		printf("x %d y %d z %d\n", x_act, y_act, ft_atoi(split_line[x_act]));

t_map	*parse_map(const char *string)
{
	int		fd;
	char	*line;
	int		width;
	int		height;
	int		y_act;
	t_map	*result;

	y_act = 0;
	fd = open(string, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (measure_map(string,&width, &height))
		return (NULL);
	result = new_map(width, height);
	while (gnl(fd, &line))
	{
		if (parse_line(line, result, y_act))
		{
			free(line);
			return (free_map(&result));
		}
		free(line);
		y_act++;
	}
	gnl(fd, NULL);
	close(fd);
	return (result);
}
