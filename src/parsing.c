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

t_map	*new_map(size_t width, size_t height)
{
	t_map	*result;

	result = malloc(sizeof(t_map));
	if (! result)
		return (NULL);
	result->grid = malloc((width + 1) * sizeof (t_point *));
	if (! result->grid)
		return (NULL);
	result->grid[width] = NULL;
	while (width--)
	{
		result->grid[width] = malloc((height) * sizeof(t_point));
		if (! result->grid[width])
		{
			free_2d_array((void **)result->grid);
			free(result);
			return (NULL);
		}
	}
	return (result);
}

void parse_line(char *line, t_map *map)
{

}

t_map	*parse_map(const char *string)
{
	int		fd;
	char	*line;
	t_map	*result;
	int		width;
	int		height;

	fd = open(string, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (measure_map(string,&width, &height))
		return (NULL);
	result = new_map(width, height);
	while (gnl(fd, &line))
	{
		break;
	}
	//gnl(fd, NULL);
	close(fd);
	return (result);
}
