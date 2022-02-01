/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:44:38 by                   #+#    #+#             */
/*   Updated: 2022/02/01 15:00:12 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	draw_1px_to_img(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	turn_all_pixels_black(t_data *img)
{
	int	x;
	int	y;

	x = 0;
	while (x < img->win_size.x_max)
	{
		y = 0;
		while (y < img->win_size.y_max)
		{
			draw_1px_to_img(img, x, y, 0);
			y++;
		}
		x++;
	}
}

void	draw_grid(t_map *map, t_data *img)
{
	int		x;
	int		y;
	t_point	*p0;

	x = 0;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			p0 = &map->grid_iso[x][y];
			if (y < map->height - 1)
				draw_line(*p0, map->grid_iso[x][y + 1], img);
			if (x < map->width - 1)
				draw_line(*p0, map->grid_iso[x + 1][y], img);
			y++;
		}
		x++;
	}
}
