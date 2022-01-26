#include "FdF.h"

void cart2iso(t_point *in)
{
	double	x_tmp;
	double	y_tmp;

	x_tmp = (in->x - in->y) / sqrt(2);
	y_tmp = (in->x - 2 * in->z + in->y) / sqrt(6);
	in->x = x_tmp;
	in->y = y_tmp;
	in->z = 0;
}