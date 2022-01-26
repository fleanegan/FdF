#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "get_next_line_bonus.h"
# include "math.h"
# include <fcntl.h>

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}		t_point;

typedef struct s_map
{
	t_point	**grid;
}		t_map;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

void	plot_line(t_point p0, t_point p1, t_data *img);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	cart2iso(t_point *in);
void	print_coordinates(t_point *pt);

// parsing
t_map	*new_map(size_t width, size_t height);
int measure_map(const char *file_name, int *width, int *height);
t_map * parse_map(const char *string);
void parse_line(char *line, t_map *map);

#endif //FDF_H
