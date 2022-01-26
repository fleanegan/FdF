#include <stdio.h>
#include "FdF.h"
#include "libft.h"

int	update_above(t_point *p0, t_point *pd, t_point *ps, int err)
{
	err += (*pd).y;
	p0->x += (*ps).x;
	return (err);
}

int	update_below(t_point *p0, t_point *pd, t_point *ps, int err)
{
	err += (*pd).x;
	p0->y += (*ps).y;
	return (err);
}

void	plot_line(t_point p0, t_point p1, t_data *img)
{
	t_point	pd;
	t_point	ps;
	int		err;
	int		err2;

	puts("e");
	pd.x = (int) ft_abs(p1.x - p0.x);
	pd.y = (int) -ft_abs(p1.y - p0.y);
	ps.x = 1 - 2 * (p0.x >= p1.x);
	ps.y = 1 - 2 * (p0.y >= p1.y);
	err = pd.x + pd.y;
	while (1)
	{
		print_coordinates(&p0);
		print_coordinates(&p1);
		my_mlx_pixel_put(img, p0.x, p0.y, 0x00FF0000);
		err2 = 2 * err;
		if (((int)p0.x == (int)p1.x && (int)p0.y == (int)p1.y) \
		|| ((int)p0.x == (int)p1.x && err2 >= (int)pd.y) || ((int)err2 <= (int)pd.x && (int)p0.y == (int)p1.y))
			break ;
		if (err2 >= pd.y)
			err = update_above(&p0, &pd, &ps, err);
		if (err2 <= pd.x)
			err = update_below(&p0, &pd, &ps, err);
	}
}
