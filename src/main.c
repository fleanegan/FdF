#include <stdio.h>
#include <math.h>
#include "libft.h" 
#include "FdF.h"
#ifndef TESTING
# include <mlx.h>
#endif


void	test_pass_param(t_data *img)
{
	t_point	p0;
	t_point	p1;
	t_point	p2;
	t_point	p3;
	t_point	p4;
	t_point	p5;

	set_point(&p0, 0, 0, 0);
	set_point(&p1, 0, 0, 100);
	set_point(&p2, 50, 0, 0);
	set_point(&p3, 50, 0, 100);
	set_point(&p4, 50, 75, 0);
	set_point(&p5, 50, 75, 100);

	p0.x += 150;
	p1.x += 150;
	p2.x += 150;
	p3.x += 150;
	p4.x += 150;
	p5.x += 150;
	p0.y += 100;
	p1.y += 100;
	p2.y += 100;
	p3.y += 100;
	p4.y += 100;
	p5.y += 100;

	puts("before trans");
	print_coordinates(&p0);
	print_coordinates(&p1);
	print_coordinates(&p2);
	print_coordinates(&p3);
	print_coordinates(&p4);
	print_coordinates(&p5);

	draw_line(p0, p1, img);
	//draw_line(p1, p3, img);
	draw_line(p3, p5, img);
	draw_line(p5, p4, img);
	draw_line(p4, p2, img);
	draw_line(p0, p2, img);

	p0.x -= 150;
	p1.x -= 150;
	p2.x -= 150;
	p3.x -= 150;
	p4.x -= 150;
	p5.x -= 150;
	p0.y -= 100;
	p1.y -= 100;
	p2.y -= 100;
	p3.y -= 100;
	p4.y -= 100;
	p5.y -= 100;

	cart2iso(&p0);
	cart2iso(&p1);
	cart2iso(&p2);
	cart2iso(&p3);
	cart2iso(&p4);
	cart2iso(&p5);

	puts("after trans");
	print_coordinates(&p0);
	print_coordinates(&p1);
	print_coordinates(&p2);
	print_coordinates(&p3);
	print_coordinates(&p4);
	print_coordinates(&p5);

	p0.x += 150;
	p1.x += 150;
	p2.x += 150;
	p3.x += 150;
	p4.x += 150;
	p5.x += 150;
	p0.y += 100;
	p1.y += 100;
	p2.y += 100;
	p3.y += 100;
	p4.y += 100;
	p5.y += 100;
	draw_line(p0, p1, img);
	//draw_line(p1, p3, img);
	draw_line(p3, p5, img);
	draw_line(p5, p4, img);
	draw_line(p4, p2, img);
	draw_line(p0, p2, img);
	puts("reached end");
}

void	dummy(t_data *img, char *file_name)
{
	t_map	*map = parse_map(file_name);
	if (! map)
	{
		ft_putendl_fd("map emptey sa mer", 1);
		return ;
	}
	zoom_grid(map, 35, 3);
	project_grid(map);
	zoom_grid(map, 1./35., 1./3.);
	t_dimension_2d current_dimensions = measure_necessary_screen_space(map);
	printf("height %d, curr ymin %d, curr ymax %d\n", img->window_size.y_max, current_dimensions.y_min, current_dimensions.y_max);
	printf("width %d, curr xmin %d, curr xmax %d\n", img->window_size.x_max, current_dimensions.x_min, current_dimensions.x_max);
	zoom_grid(map, 0.85 * calc_zoom_factor(&current_dimensions, &img->window_size), 0);
	current_dimensions = measure_necessary_screen_space(map);
	move_grid(map, (img->window_size.x_max - current_dimensions.x_min - current_dimensions.x_max) / 2,(img->window_size.y_max - current_dimensions.y_max) / 2, 0);
	draw_grid(map, img);
	printf("height %d, curr ymin %d, curr ymax %d\n", img->window_size.y_max, current_dimensions.y_min, current_dimensions.y_max);
	printf("width %d, curr xmin %d, curr xmax %d\n", img->window_size.x_max, current_dimensions.x_min, current_dimensions.x_max);
}

#ifndef TESTING

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	img.window_size.x_max = 1200;
	img.window_size.y_max = 1000;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, img.window_size.x_max, img.window_size.y_max, "Hello world!");
	img.img = mlx_new_image(mlx, img.window_size.x_max, img.window_size.y_max);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	puts("before");
	//test_pass_param(&img);
	if (argc == 2)
	{
		dummy(&img, argv[1]);
		mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
		mlx_loop(mlx);
	}
	return (0);
}

#endif