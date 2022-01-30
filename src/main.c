#include <stdio.h>
#include <math.h>
#include "libft.h" 
#include "FdF.h"
#ifndef TESTING
# include <mlx.h>

void all_pixels_black(t_data *img);

#endif

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
		free_map(&img->map);
		exit(0);
	}
	return 0;
}

int render_frame(void *void_img)
{
	t_data		*img;
	static double theta = 0;

	theta += 3.1415 / 360. * 1;
	img = void_img;
	all_pixels_black(img);
	project_grid(img->map, theta);
	t_dimension_2d current_dimensions = measure_necessary_screen_space(img->map);
	zoom_grid(img->map, 0.85 * calc_zoom_factor(&current_dimensions, &img->window_size), 0, img->map->grid_iso);
	current_dimensions = measure_necessary_screen_space(img->map);
	move_grid(img->map, (img->window_size.x_max - current_dimensions.x_min - current_dimensions.x_max) / 2,
			  (img->window_size.y_max - current_dimensions.y_min - current_dimensions.y_max) / 2, 0);
	draw_grid(img->map, img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	sleep(0.1);
	return 0;
}

void	all_pixels_black(t_data *img)
{
	int	x;
	int	y;

	x = 0;
	while (x < img->window_size.x_max)
	{
		y = 0;
		while (y < img->window_size.y_max)
		{
			my_mlx_pixel_put(img, x, y, 0);
			y++;
		}
		x++;
	}
}

#ifndef TESTING

int	main(int argc, char **argv)
{
	t_data	img;

	img.window_size.x_max = 1000;
	img.window_size.y_max = 900;
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, img.window_size.x_max, img.window_size.y_max, "Hello world!");
	img.img = mlx_new_image(img.mlx, img.window_size.x_max, img.window_size.y_max);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	if (argc == 2)
	{
		img.map = parse_map(argv[1]);
		if (! img.map) {
			ft_putendl_fd("img->map emptey sa mer", 1);
			return (1);
		}
		//zoom_grid(img->map, 1, 1, img->map->grid_cart);
		mlx_key_hook(img.mlx_win, free_mlx, &img);
		mlx_loop_hook(img.mlx, render_frame, &img);
		mlx_loop(img.mlx);
		puts("stopped");
	}
	return (0);
}

#endif
 //*/