/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_grid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:43:44 by                   #+#    #+#             */
/*   Updated: 2022/02/01 18:17:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	zoom_grid(t_map *map, float zoom, t_point **grid)
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
			p0 = &grid[x][y];
			set_point(\
			p0, p0->x * zoom, p0->y * zoom, p0->z * zoom);
			y++;
		}
		x++;
	}
}

void	move_grid(t_map *map, int x_off, int y_off, int z_off)
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
			set_point(p0, p0->x + x_off, p0->y + y_off, p0->z + z_off);
			y++;
		}
		x++;
	}
}

void	apply_transformations_to_grid(\
		t_map *map, t_rot_matrix rot_mat, float z_scale)
{
	int		x;
	int		y;
	t_point	*p_cart;
	t_point	*p_iso;

	x = 0;
	while (x < map->width)
	{
		y = 0;
		while (y < map->height)
		{
			p_cart = &map->grid_cart[x][y];
			p_iso = &map->grid_iso[x][y];
			apply_transformations_to_point(p_cart, p_iso, rot_mat, z_scale);
			y++;
		}
		x++;
	}
}

void	apply_transformations_to_point(\
		t_point *in, t_point *out, t_rot_matrix rot_mat, float z_scale)
{
	set_point(out, in->x, in->y, in->z * z_scale);
	rotate_point(out, &rot_mat);
	out->z = in->z * z_scale;
}
