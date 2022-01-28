#include <stdio.h>
#include <math.h>
#include "libft.h" 
#include "FdF.h"
#ifndef TESTING
# include <mlx.h>
#endif

void	dummy(t_data *img)
{
	zoom_grid(img->map, 1, 1);
	project_grid(img->map);
	t_dimension_2d current_dimensions = measure_necessary_screen_space(img->map);
	zoom_grid(img->map, 0.85 * calc_zoom_factor(&current_dimensions, &img->window_size), 0);
	current_dimensions = measure_necessary_screen_space(img->map);
	move_grid(img->map, (img->window_size.x_max - current_dimensions.x_min - current_dimensions.x_max) / 2,(img->window_size.y_max - current_dimensions.y_min - current_dimensions.y_max) / 2, 0);
	draw_grid(img->map, img);
}
//printf("height %d, curr ymin %d, curr ymax %d\n", img->window_size.y_max, current_dimensions.y_min, current_dimensions.y_max);
//printf("width %d, curr xmin %d, curr xmax %d\n", img->window_size.x_max, current_dimensions.x_min, current_dimensions.x_max);

//*
int free_mlx(int keycode, t_data *img)
{
	if (keycode == 65307)
	{
		mlx_loop_end(img->mlx);
		mlx_destroy_image(img->mlx, img->img);
		mlx_destroy_window(img->mlx, img->mlx_win);
		mlx_destroy_display(img->mlx);
		free(img->mlx);
		free_2d_array((void **)img->map->grid);
		free(img->map);
		exit(0);
	}
	return 0;
}

int init_mlx(t_data *img)
{
	(*img).window_size.x_max = 2200;
	(*img).window_size.y_max = 1000;
	(*img).mlx = mlx_init();
	(*img).mlx_win = mlx_new_window((*img).mlx, (*img).window_size.x_max, (*img).window_size.y_max, "Fild D'enFer");
	(*img).img = mlx_new_image((*img).mlx, (*img).window_size.x_max, (*img).window_size.y_max);
	(*img).addr = mlx_get_data_addr((*img).img, &(*img).bits_per_pixel, &(*img).line_length, &(*img).endian);
	return (0);
}

#ifndef TESTING



int	main(int argc, char **argv)
{
	t_data	img;

	if (argc != 2)
		return (1);
	img.map = parse_map(argv[1]);
	if (! img.map)
		return (1);
	init_mlx(&img);
	dummy(&img);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_key_hook(img.mlx_win, free_mlx, &img);
	mlx_loop(img.mlx);
	puts("stopped");
	return (0);
}

#endif