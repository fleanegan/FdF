/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:45:00 by                   #+#    #+#             */
/*   Updated: 2022/02/01 14:45:00 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"

void	print_coordinates(t_point *pt)
{
	ft_putstr_fd("x: ", 1);
	ft_putnbr_fd((int)pt->x, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("y: ", 1);
	ft_putnbr_fd((int)pt->y, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("z: ", 1);
	ft_putnbr_fd((int)pt->z, 1);
	ft_putstr_fd("\n", 1);
}
