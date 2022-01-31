#include <stdio.h>
#include <math.h>
#include "libft.h" 
#include "FdF.h"
#ifndef TESTING
# include <mlx.h>

void all_pixels_black(t_data *img);
int render_frame(void *void_img);

#endif

//*
int key_handler(int keycode, t_data *img)
{
	printf("ke %d\n", keycode);
	if (keycode == 65307 || keycode == 38)
	{
		mlx_loop_end(img->mlx);
		mlx_destroy_image(img->mlx, img->img);
		mlx_destroy_window(img->mlx, img->mlx_win);
		mlx_destroy_display(img->mlx);
		free(img->mlx);
		free_map(&img->map);
		exit(0);
	}
	if (keycode == 65361)
		img->alpha += 3.1415 / 360. * 5;
	if (keycode == 65363)
		img->alpha -= 3.1415 / 360. * 5;
	if (keycode == 65362)
		img->beta += 3.1415 / 360. * 5;
	if (keycode == 65364)
		img->beta -= 3.1415 / 360. * 5;
	render_frame(img);
	return 0;
}

void init_view(t_data *img) {
	t_dimension_2d	current_dimensions;
	float			factor;

	project_grid(img->map, 0, 0);
	current_dimensions = measure_necessary_screen_space(img->map);
	factor = calc_zoom_factor(&current_dimensions, &img->window_size);
	zoom_grid(img->map, 0.85 * factor, 0.85 * factor, img->map->grid_cart);
	current_dimensions = measure_necessary_screen_space(img->map);
}

int render_frame(void *void_img)
{
	t_data		*img;
	t_dimension_2d	current_dimensions;

	img = void_img;
	all_pixels_black(img);
	project_grid(img->map, img->alpha, img->beta);
	current_dimensions = measure_necessary_screen_space(img->map);
	move_grid(img->map, (img->window_size.x_max - current_dimensions.x_min - current_dimensions.x_max) / 2,
			  (img->window_size.y_max - current_dimensions.y_min - current_dimensions.y_max) / 2, 0);
	draw_grid(img->map, img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
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
	img.alpha = 0;
	img.beta = 0;
	if (argc == 2)
	{
		img.map = parse_map(argv[1]);
		if (! img.map) {
			ft_putendl_fd("img->map emptey sa mer", 1);
			return (1);
		}
		init_view(&img);
		//zoom_grid(img->map, 1, 1, img->map->grid_cart);
		mlx_key_hook(img.mlx_win, key_handler, &img);
		//mlx_loop_hook(img.mlx, render_frame, &img);
		mlx_loop(img.mlx);
		puts("stopped");
	}
	return (0);
}

#endif
 //*/