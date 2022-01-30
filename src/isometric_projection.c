#include <stdio.h>
#include "FdF.h"

t_dimension_2d	init_t_dimension(t_dimension_2d *result);
t_dimension_2d	update_extrema(t_dimension_2d *result, t_point *p);

void cart2iso(t_point *in, t_point *out, double theta)
{
	double	x_tmp;
	double	y_tmp;
	double	x_rot;
	double	y_rot;

	x_rot = cos(theta) * in->x - sin(theta) * in->y;
	y_rot = sin(theta) * in->x + cos(theta) * in->y;
	x_tmp = (x_rot - y_rot) / sqrt(2);
	y_tmp = (x_rot - 2 * in->z + y_rot) / sqrt(6);
	out->x = x_tmp;
	out->y = y_tmp;
	out->z = 0;
}

t_dimension_2d	measure_necessary_screen_space(t_map *map)
{
	t_dimension_2d	result;
	t_point		p;
	int			x;
	int			y;

	x = 0;
	result = init_t_dimension(&result);
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			p = map->grid_iso[x][y];
			result = update_extrema(&result, &p);
			y++;
		}
		x++;
	}
	return (result);
}

t_dimension_2d	update_extrema(t_dimension_2d *result, t_point *p)
{
	if ((*p).x < (*result).x_min)
		(*result).x_min = (int)(*p).x;
	else if ((*p).x > (*result).x_max)
		(*result).x_max = (int)(*p).x;
	if ((*p).y < (*result).y_min)
		(*result).y_min = (int)(*p).y;
	else if ((*p).y > (*result).y_max)
		(*result).y_max = (int)(*p).y;
	return (*result);
}

t_dimension_2d	init_t_dimension(t_dimension_2d *result)
{
	(*result).x_min = 0;
	(*result).x_max = 0;
	(*result).y_min = 0;
	(*result).y_max = 0;
	return (*result);
}

float	calc_zoom_factor(t_dimension_2d *img, t_dimension_2d *screen)
{
	int		x_span_img;
	int		y_span_img;
	float	zoom_x;
	float	zoom_y;

	x_span_img = img->x_max - img->x_min + 1;
	y_span_img = img->y_max - img->y_min + 1;
	zoom_x = (float) screen->x_max / (float) x_span_img;
	zoom_y = (float) screen->y_max / (float) y_span_img;
	if (zoom_x < zoom_y)
		return (zoom_x);
	return (zoom_y);
}
// printf("screen x %d screen y %d xoom %f yoom %f xspan %d yspan %d\n",screen->x_max, screen->y_max ,zoom_x, zoom_y, x_span_img, y_span_img);
