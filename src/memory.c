/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:44:33 by                   #+#    #+#             */
/*   Updated: 2022/02/01 14:44:35 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	set_point(t_point *pt, double x, double y, double z)
{
	pt->x = x;
	pt->y = y;
	pt->z = z;
}

t_point	**new_grid(t_map *map)
{
	t_point	**result;
	int		width;

	width = map->width;
	result = malloc((width + 1) * sizeof (t_point *));
	if (! result)
		return (NULL);
	result[width] = NULL;
	while (width--)
	{
		result[width] = malloc((map->height) * sizeof(t_point));
		if (! result[width])
		{
			free_2d_array((void **) result);
			return (NULL);
		}
	}
	return (result);
}

t_map	*new_map(int width, int height)
{
	t_map	*result;

	result = malloc(sizeof(t_map));
	if (! result)
		return (NULL);
	result->width = width;
	result->height = height;
	result->grid_iso = NULL;
	result->grid_cart = new_grid(result);
	if (! result->grid_cart)
		return (free_map(&result));
	result->grid_iso = new_grid(result);
	if (! result->grid_iso)
		return (free_map(&result));
	return (result);
}

void	*free_map(t_map **map)
{
	free_2d_array((void **)(*map)->grid_cart);
	free_2d_array((void **)(*map)->grid_iso);
	free(*map);
	*map = NULL;
	return (NULL);
}
