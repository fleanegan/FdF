/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:44:19 by                   #+#    #+#             */
/*   Updated: 2022/02/01 18:16:11 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "FdF.h"
#include <mlx.h>

void	tear_down_mlx_session(t_data *img)
{
	mlx_loop_end(img->mlx);
	mlx_destroy_image(img->mlx, img->img);
	mlx_destroy_window(img->mlx, img->mlx_win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	free_map(&img->map);
	exit(0);
}

int	render_frame(void *void_img)
{
	t_data			*img;
	t_dimension_2d	dimensions_act;

	img = void_img;
	turn_all_pixels_black(img);
	apply_transformations_to_grid(img->map, img->orientation, img->z_scale);
	dimensions_act = measure_necessary_screen_space(img->map);
	move_grid(img->map, \
	(double)(img->win_size.x_max - dimensions_act.x_min - dimensions_act.x_max) \
		/ 2. * img->x_offset, \
	(double)(img->win_size.y_max - dimensions_act.y_min - dimensions_act.y_max) \
		/ 2. * img->y_offset, 0);
	zoom_grid(img->map, img->zoom, img->map->grid_iso);
	draw_grid(img->map, img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	return (0);
}

t_data	init_mlx(void)
{
	t_data	img;

	img.win_size.x_max = 1000;
	img.win_size.y_max = 900;
	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(\
		img.mlx, img.win_size.x_max, img.win_size.y_max, "Fils D'enFer");
	img.img = mlx_new_image(img.mlx, img.win_size.x_max, img.win_size.y_max);
	img.addr = mlx_get_data_addr(\
	img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	return (img);
}

#ifndef TESTING

int	main(int argc, char **argv)
{
	t_data	img;

	img = init_mlx();
	if (argc == 2)
	{
		img.map = parse_map(argv[1]);
		if (! img.map)
		{
			ft_putendl_fd("img->map emptey sa mer", 1);
			return (1);
		}
		init_view(&img);
		mlx_key_hook(img.mlx_win, key_handler, &img);
		mlx_loop(img.mlx);
		puts("stopped");
	}
	return (0);
}

#endif