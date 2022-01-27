#include "test_utils.h"

Test(test_calc_zoom_level, measure_flat_map_returns_xy_size)
{
	t_map *map = new_map(2, 2);
	parse_line("0 1", map, 0);
	parse_line("2 3", map, 1);

	t_dimension_2d result = measure_necessary_screen_space(map);
	cr_assert_eq(result.x_max, 1);
	cr_assert_eq(result.x_min, 0);
	cr_assert_eq(result.y_max, 1);
	cr_assert_eq(result.y_min, 0);
}

Test(test_calc_zoom_level, if_screen_size_double_of_needed_return_two)
{
	t_dimension_2d img_dimensions;
	img_dimensions.x_min = -1;
	img_dimensions.x_max = 1;
	img_dimensions.y_min = -1;
	img_dimensions.y_max = 1;
	t_dimension_2d screen_dimensions;
	screen_dimensions.x_min = 0;
	screen_dimensions.x_max = 6;
	screen_dimensions.y_min = 0;
	screen_dimensions.y_max = 6;

	float	factor = calc_zoom_factor(&img_dimensions, &screen_dimensions);
	cr_assert_float_eq(factor, 2., 0.002);
}