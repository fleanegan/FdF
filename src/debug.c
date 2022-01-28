#include "FdF.h"

void	print_coordinates(t_point *pt)
{
	ft_putstr_fd("x_cart: ", 1);
	ft_putnbr_fd((int)pt->x_cart, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("y_cart: ", 1);
	ft_putnbr_fd((int)pt->y_cart, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("z_cart: ", 1);
	ft_putnbr_fd((int)pt->z_cart, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("x_iso: ", 1);
	ft_putnbr_fd((int)pt->x_iso, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("y_iso: ", 1);
	ft_putnbr_fd((int)pt->y_iso, 1);
	ft_putstr_fd("\n", 1);
}
