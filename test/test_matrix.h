#include "test_utils.h"

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

Test(test_matrix, rotation_with_zero_deg_results_in_identity_matrix)
{
	t_rotation_matrix t = euler2rot(0., 0., 0.);
	cr_assert_identity(&t);
}

Test(test_matrix, dot_product_with_negative_and_positive_entries, .disabled=true)
{
	t_rotation_matrix a = euler2rot(0., 0., 0.);
	t_rotation_matrix b = euler2rot(0., 0., 0.);
	zero_init_rotation_matrix(&a);
	zero_init_rotation_matrix(&b);
	a.mat[0][0] = -9;
	a.mat[1][0] = 29;
	a.mat[2][0] = 0;
	a.mat[0][1] = 4;
	a.mat[1][1] = 2;
	a.mat[2][1] = 1;
	a.mat[0][2] = 0;
	a.mat[1][2] = 56;
	a.mat[2][2] = 111;
	b.mat[0][0] = 0;
	b.mat[1][0] = 209;
	b.mat[2][0] = 10;
	b.mat[0][1] = 40;
	b.mat[1][1] = -20;
	b.mat[2][1] = 10;
	b.mat[0][2] = 0.7;
	b.mat[1][2] = 506;
	b.mat[2][2] = 5;
	t_rotation_matrix t = multiply(&a, b);
	t_rotation_matrix c = euler2rot(0., 0., 0.);
	c.mat[0][0] = 1160;
	c.mat[1][0] = -2461;
	c.mat[2][0] = 200;
	c.mat[0][1] = 80.7;
	c.mat[1][1] = 1302;
	c.mat[2][1] = 65;
	c.mat[0][2] = 2317.7;
	c.mat[1][2] = 55046;
	c.mat[2][2] = 1115;
	int count = 9;
	while(count--)
		cr_expect_float_eq(*(*t.mat + count), *(*c.mat + count), 0.001, "at %d", count);
}

Test(test_matrix, rotating_point_in_xy_plane)
{
	t_rotation_matrix rotation_matrix = euler2rot(0., 0., 90.);
	t_point	point;
	set_point(&point, 1, 0, 0);
	rotate_point(&point, &rotation_matrix);
	cr_assert_float_eq(point.x, 0, 0.01);
	cr_assert_float_eq(point.y, 1, 0.01);
}