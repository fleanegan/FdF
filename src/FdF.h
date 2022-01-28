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

typedef struct s_dimension_2d
{
	int	x_max;
	int	x_min;
	int	y_max;
	int	y_min;
}		t_dimension_2d;

typedef struct s_map
{
	t_point	**grid;
	int		width;
	int		height;
}		t_map;

typedef struct s_data {
	void			*img;
	char			*addr;
	void			*mlx;
	void			*mlx_win;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_dimension_2d	window_size;
	t_map			*map;
}	t_data;

void			draw_line(t_point p0, t_point p1, t_data *img);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			cart2iso(t_point *in);
void			print_coordinates(t_point *pt);
void			draw_grid(t_map *map, t_data *img);
void			zoom_grid(t_map *map, float xy_factor, float z_factor);
void			project_grid(t_map *map);
void			move_grid(t_map *map, int x_off, int y_off, int z_off);
t_dimension_2d	measure_necessary_screen_space(t_map *map);
float	calc_zoom_factor(t_dimension_2d *img, t_dimension_2d *screen);


// parsing
t_map	*new_map(int width, int height);
int measure_map(const char *file_name, int *width, int *height);
t_map * parse_map(const char *string);
int parse_line(char *line, t_map *map, int y_act);
void	set_point(t_point *pt, double x, double y, double z);

#endif //FDF_H
