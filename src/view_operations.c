/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:44:27 by                   #+#    #+#             */
/*   Updated: 2022/02/01 14:51:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

static t_dimension_2d	update_extrema(t_dimension_2d *result, t_point *p);

void	init_view(t_data *img)
{
	t_dimension_2d	current_dimensions;
	float			factor;

	img->orientation = init_with_isometric_orientation();
	apply_transformations_to_grid(img->map, img->orientation, 0);
	current_dimensions = measure_necessary_screen_space(img->map);
	factor = calc_zoom_factor(&current_dimensions, &img->win_size);
	zoom_grid(img->map, 0.85f * factor, 0.85f * factor, img->map->grid_cart);
	current_dimensions = measure_necessary_screen_space(img->map);
	img->z_scale = 1;
}

t_dimension_2d	measure_necessary_screen_space(t_map *map)
{
	t_dimension_2d	result;
	t_point			p;
	int				x;
	int				y;

	x = 0;
	result.x_min = 0;
	result.x_max = 0;
	result.y_min = 0;
	result.y_max = 0;
	result = (*&result);
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

t_rot_matrix	init_with_isometric_orientation(void)
{
	t_rot_matrix	result;
	t_rot_matrix	tmp;

	result = euler2rot(90 - 35, 0, 0);
	tmp = euler2rot(0, 0, 45);
	result = multiply(&result, tmp);
	return (result);
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
