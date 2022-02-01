/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:43:57 by                   #+#    #+#             */
/*   Updated: 2022/02/01 17:41:52 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "FdF.h"

void	zero_init_rotation_matrix(t_rot_matrix *t)
{
	ft_bzero(t, sizeof((*t)));
	t->height = 3;
	t->width = 3;
}

t_rot_matrix	euler2rot(\
					double alpha_deg, double beta_deg, double gamma_deg)
{
	t_rot_matrix	result;
	double			u;
	double			v;
	double			w;

	zero_init_rotation_matrix(&result);
	u = M_PI / 180. * alpha_deg;
	v = M_PI / 180. * beta_deg;
	w = M_PI / 180. * gamma_deg;
	result.mat[0][0] = cos(v) * cos(w);
	result.mat[1][0] = sin(u) * sin(v) * cos(w) - cos(u) * sin(w);
	result.mat[2][0] = sin(u) * sin(w) + cos(u) * sin(v) * cos(w);
	result.mat[0][1] = cos(v) * sin(w);
	result.mat[1][1] = cos(u) * cos(w) + sin(u) * sin(v) * sin(w);
	result.mat[2][1] = cos(u) * sin(v) * sin(w) - sin(u) * cos(w);
	result.mat[0][2] = -sin(v);
	result.mat[1][2] = sin(u) * cos(v);
	result.mat[2][2] = cos(u) * cos(v);
	return (result);
}

t_rot_matrix	multiply(t_rot_matrix *a, t_rot_matrix b)
{
	t_rot_matrix	result;
	int				x;
	int				y;
	int				n;

	zero_init_rotation_matrix(&result);
	if (a->width != b.height)
		return (result);
	x = -1;
	while (++x < a->width)
	{
		y = -1;
		while (++y < b.height)
		{
			n = -1;
			while (++n < a->width)
				result.mat[x][y] += a->mat[n][y] * b.mat[x][n];
		}
	}
	return (result);
}

void	rotate_point(t_point *p, t_rot_matrix *mat)
{
	t_point	tmp;

	tmp.x = \
		mat->mat[0][0] * p->x + mat->mat[1][0] * p->y + mat->mat[2][0] * p->z;
	tmp.y = \
		mat->mat[0][1] * p->x + mat->mat[1][1] * p->y + mat->mat[2][1] * p->z;
	tmp.z = \
		mat->mat[0][2] * p->x + mat->mat[1][2] * p->y + mat->mat[2][2] * p->z;
	p->x = tmp.x;
	p->y = tmp.y;
	p->z = tmp.z;
}
