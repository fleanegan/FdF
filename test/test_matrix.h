#include "test_utils.h"

typedef struct t_rotation_matrix
{
	double	mat[3][3];
	int		width;
	int		height;
}			t_rotation_matrix;

void zero_init_rotation_matrix(t_rotation_matrix *t)
{
	bzero(t, sizeof((*t)));
	t->height = 3;
	t->width = 3;
}

t_rotation_matrix rot_from_euler(double alpha_deg, double beta_deg, double gamma_deg)
{
	t_rotation_matrix	result;
	double				u;
	double				v;
	double				w;

	zero_init_rotation_matrix(&result);
	// maybe bug here wtf
	u = M_PI / 360. * alpha_deg;
	v = M_PI / 360. * beta_deg;
	w = M_PI / 360. * gamma_deg;
	result.mat[0][0] = cos(v) * cos(w);
	result.mat[1][0] = sin(u) * sin(v) * cos(w) - cos(u) * sin(w);
	result.mat[2][0] = sin(u) * sin(w) + cos(u) * sin(v) * cos(w);
	result.mat[0][1] = cos(v) * sin(w);
	result.mat[1][1] = cos(u) * cos(w) + sin(u) * sin(v)* sin(w);
	result.mat[2][1] = cos(u) * sin(v) * sin(w) - sin(u) * cos(w);
	result.mat[0][2] = -sin(v);
	result.mat[1][2] = sin(u) * cos(v);
	result.mat[2][2] = cos(u) * cos(v);
	return result;
}

void cr_assert_identity(t_rotation_matrix *t)
{
	cr_assert_float_eq((*t).mat[0][0], 1, 0.001);
	cr_assert_float_eq((*t).mat[1][0], 0, 0.001);
	cr_assert_float_eq((*t).mat[2][0], 0, 0.001);
	cr_assert_float_eq((*t).mat[0][1], 0, 0.001);
	cr_assert_float_eq((*t).mat[1][1], 1, 0.001);
	cr_assert_float_eq((*t).mat[2][1], 0, 0.001);
	cr_assert_float_eq((*t).mat[0][2], 0, 0.001);
	cr_assert_float_eq((*t).mat[1][2], 0, 0.001);
	cr_assert_float_eq((*t).mat[2][2], 1, 0.001);
}

t_rotation_matrix dot_product(t_rotation_matrix *a, t_rotation_matrix *b)
{
	t_rotation_matrix	result;
	int					x;
	int					y;
	int					n;

	zero_init_rotation_matrix(&result);
	if (a->width != b->height)
		return (result);
	x = 0;
	while (x < a->width)
	{
		y = -1;
		while (++y < b->height)
		{
			n = -1;
			while (++n < a->width)
			{
				double tmp_r = a->mat[x][n] * b->mat[n][y];
				result.mat[x][y] += tmp_r;
			}
		}
		x++;
	}
	return result;
}

void print_matrix(t_rotation_matrix *a)
{
	int					x;
	int					y;

	y = 0;
	printf("height %d width %d\n", a->height, a->width);
	while (y < a->height)
	{
		x = 0;
		while (x < a->width)
		{
			printf("%f ", a->mat[x][y]);
			x++;
		}
		printf("\n");
		y++;
	}
}

Test(test_matrix, rotation_with_zero_deg_results_in_identity_matrix)
{
	t_rotation_matrix t = rot_from_euler(0., 0., 0.);
	cr_assert_identity(&t);
}

Test(test_matrix, two_additions_equal_one_big_rotation)
{
	t_rotation_matrix a = rot_from_euler(50., 0., 0.);
	t_rotation_matrix b = rot_from_euler(50., 0., 0.);
	t_rotation_matrix t = dot_product(&a, &b);
	cr_assert_eq(t.width, 3);
	cr_assert_eq(t.height, 3);
	t_rotation_matrix c = rot_from_euler(100., 0., 0.);
	int count = sizeof(t_rotation_matrix) / sizeof(double);
	while(count--)
		cr_assert_float_eq(*(*t.mat + count), *(*c.mat + count), 0.001, "T %f, C %f", *(*t.mat + count), *(*c.mat + count));
}

void rotate_point(t_point *p, t_rotation_matrix *mat)
{
	t_point	tmp;
	printf("0: %f, 1: %f\n", mat->mat[0][0] * p->x, mat->mat[1][0] * p->y);
	tmp.x = mat->mat[0][0] * p->x + mat->mat[1][0] * p->y + mat->mat[2][0] * p->z;
	printf("tmp x: %f\n", tmp.x);
	tmp.y = mat->mat[0][1] * p->x + mat->mat[1][1] * p->y + mat->mat[2][1] * p->z;
	tmp.z = mat->mat[0][2] * p->x + mat->mat[1][2] * p->y + mat->mat[2][2] * p->z;
	p->x = 33;
	p->x = tmp.x;
	p->y = tmp.y;
	p->z = tmp.z;
	printf("tmp after x: %f\n", tmp.x);

}

Test(test_matrix, rotating_point_in_xy_plane)
{
	t_rotation_matrix rotation_matrix = rot_from_euler(0., 0., 90.);
	print_matrix(&rotation_matrix);
	t_point	*point = new_point(1, 0, 0);
	rotate_point(point, &rotation_matrix);
	printf("x: %f, y: %f, z: %f\n", point->x, point->y, point->z);
	cr_assert_float_eq(point->x, 0, 0.01);
	cr_assert_float_eq(point->y, 1, 0.01);
	free(point);
}