#include <stdio.h>
#include <math.h>
#include "libft.h" 
#include <mlx.h>
#include "FdF.h"

void	set_point(t_point *pt, double x, double y, double z)
{
	pt->x = x;
	pt->y = y;
	pt->z = z;
}

void	print_coordinates(t_point *pt)
{
	printf("x %f, y %f, z %f\n", pt->x, pt->y, pt->z);
}

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

	plot_line(p0, p1, img);
	//plot_line(p1, p3, img);
	plot_line(p3, p5, img);
	plot_line(p5, p4, img);
	plot_line(p4, p2, img);
	plot_line(p0, p2, img);

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
	plot_line(p0, p1, img);
	//plot_line(p1, p3, img);
	plot_line(p3, p5, img);
	plot_line(p5, p4, img);
	plot_line(p4, p2, img);
	plot_line(p0, p2, img);
	puts("reached end");
}

int	main()
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 300, 300, "Hello world!");
	img.img = mlx_new_image(mlx, 300, 300);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	puts("before");
	test_pass_param(&img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	(void) mlx_win;
	return (0);
}
