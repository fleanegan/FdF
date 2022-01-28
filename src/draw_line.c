#include <stdio.h>
#include "FdF.h"
#include "libft.h"

int	update_above(t_point *p0, t_point *pd, t_point *ps, int err)
{
	err += (*pd).y_cart;
	p0->x_cart += (*ps).x_cart;
	return (err);
}

int	update_below(t_point *p0, t_point *pd, t_point *ps, int err)
{
	err += (*pd).x_cart;
	p0->y_cart += (*ps).y_cart;
	return (err);
}

void	draw_line(t_point p0, t_point p1, t_data *img)
{
	t_point	pd;
	t_point	ps;
	int		err;
	int		err2;

	print_coordinates(&p0);
	print_coordinates(&p1);
	pd.x_iso = (int) ft_abs(p1.x_iso - p0.x_iso);
	pd.y_iso = (int) -ft_abs(p1.y_iso - p0.y_iso);
	ps.x_iso = 1 - 2 * (p0.x_iso >= p1.x_iso);
	ps.y_iso = 1 - 2 * (p0.y_iso >= p1.y_iso);
	err = pd.x_iso + pd.y_iso;
	while (1)
	{
//		print_coordinates(&p0);
//		print_coordinates(&p1);
		if (p0.x_iso < 0 || p0.y_iso < 0 || p0.x_iso >= img->window_size.x_max || p0.y_iso >= img->window_size.y_max)
		{
			print_coordinates(&p0);
			print_coordinates(&p1);
			return ;
		}
		my_mlx_pixel_put(img, p0.x_iso, p0.y_iso, 0x00FF0000);
		err2 = 2 * err;
		if (((int)p0.x_iso == (int)p1.x_iso && (int)p0.y_iso == (int)p1.y_iso) \
 || ((int)p0.x_iso == (int)p1.x_iso && err2 >= (int)pd.y_iso) || ((int)err2 <= (int)pd.x_iso && (int)p0.y_iso == (int)p1.y_iso))
			break ;
		if (err2 >= pd.y_iso)
			err = update_above(&p0, &pd, &ps, err);
		if (err2 <= pd.x_iso)
			err = update_below(&p0, &pd, &ps, err);
	}
}
