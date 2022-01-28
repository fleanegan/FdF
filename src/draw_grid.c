#include "FdF.h"

void	draw_grid(t_map *map, t_data *img)
{
	int		x;
	int		y;
	t_point	*p0;
	t_point	*p1;

	x = 0;
	while (x < map->width) {
		y = 0;
		while (y < map->height)
		{
			p0 = &map->grid[x][y];
			if (y < map->height - 1)
			{
				p1 = &map->grid[x][y + 1];
//				print_coordinates(p0);
//				print_coordinates(p1);
				draw_line(*p0, *p1, img);
			}
			if (x < map->width - 1)
			{
				p1 = &map->grid[x + 1][y];
//				print_coordinates(p0);
//				print_coordinates(p1);
				draw_line(*p0, *p1, img);
			}
			y++;
		}
		x++;
	}
}

void zoom_grid(t_map *map, float factor)
{
	int		x;
	int		y;
	t_point	*p0;

	x = 0;
	y = 0;
	while (x < map->width) {
		y = 0;
		while (y < map->height)
		{
			p0 = &map->grid[x][y];
			set_point_iso(p0, p0->x_iso * factor, p0->y_iso * factor);
			y++;
		}
		x++;
	}
}

void	project_grid(t_map *map)
{
	int		x;
	int		y;
	t_point	*p0;

	x = 0;
	y = 0;
	while (x < map->width) {
		y = 0;
		while (y < map->height)
		{
			p0 = &map->grid[x][y];
			cart2iso(p0);
			y++;
		}
		x++;
	}
}

void	move_grid(t_map *map, int x_off, int y_off)
{
	int		x;
	int		y;
	t_point	*p0;

	x = 0;
	y = 0;
	while (x < map->width) {
		y = 0;
		while (y < map->height)
		{
			p0 = &map->grid[x][y];
			set_point_iso(p0, p0->x_iso + x_off, p0->y_iso + y_off);
			y++;
		}
		x++;
	}
}