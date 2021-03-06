#include "test_utils.h"

Test(test_parsing, return_NULL_if_no_valid_map_entered)
{
	t_map *map = parse_map("invalid_file_name");

	cr_assert_null(map);
}

Test(test_parsing, get_map_dimensions_for_invalid_file_returns_1)
{
	int result = measure_map("invalid_file_name", NULL, NULL);

	cr_assert_eq(result, -1);
}

Test(test_parsing, get_map_dimensions_for_file_with_one_entry)
{
	int	width;
	int	heigth;

	measure_map("assets/dummy_map_one_point", &width, &heigth);

	cr_assert_eq(width, 1);
	cr_assert_eq(heigth, 1);
}

Test(test_parsing, get_map_dimensions_for_file_with_one_row_and_two_columns)
{
	int	width;
	int	heigth;

	measure_map("assets/dummy_map_two_points", &width, &heigth);

	cr_assert_eq(width, 2);
	cr_assert_eq(heigth, 1);
}

Test(test_parsing, create_empty_grid_cart)
{
	t_map	*map = malloc(sizeof(t_map));
	int		width = 2;
	int		height = 2;
	map->width = width;
	map->height = height;

	t_point	**res = new_grid(map);

	cr_assert_not_null(res);
	free_2d_array((void **) res);
	free(map);
}


Test(test_parsing, create_empty_map)
{
	int	width = 2;
	int	height = 2;

	t_map *res = new_map(width, height);

	cr_assert_not_null(res);
	free_map(&res);
}


Test(test_parsing, creating_map_NULL_terminates_width)
{
	int	width = 2;
	int	height = 2;

	t_map *res = new_map(width, height);

	cr_assert_not_null(res);
	cr_assert_null(res->grid_cart[width]);
	free_map(&res);
}

Test(test_parsing, return_minus_one_if_not_all_columns_equal_len)
{
	int	width;
	int	heigth;

	int 	result = measure_map("assets/dummy_map_malformed", &width, &heigth);

	cr_assert_eq(result, -1);
}

Test(test_parsing, parse_map_with_one_point)
{
	t_map *map = parse_map("assets/dummy_map_one_point");
	t_point *only_point = (*map->grid_cart);

	cr_assert_not_null(map);
	cr_assert_not_null(only_point);
	free_map(&map);
}

Test(test_parsing, parse_one_line_with_one_column)
{
	char	*line = "1";
	t_map	*map = new_map(1, 1);

	parse_line(line, map, 0);

	cr_assert_eq(map->grid_cart[0][0].x, 0);
	cr_assert_eq(map->grid_cart[0][0].y, 0);
	cr_assert_eq(map->grid_cart[0][0].z, 1);
	free_map(&map);
}

Test(test_parsing, parse_one_line_with_two_columns)
{
	char	*line = "1 2";
	t_map	*map = new_map(2, 1);

	parse_line(line, map, 0);

	cr_assert_eq(map->grid_cart[0][0].x, 0);
	cr_assert_eq(map->grid_cart[0][0].y, 0);
	cr_assert_eq(map->grid_cart[0][0].z, 1);
	cr_assert_eq(map->grid_cart[1][0].x, 1);
	cr_assert_eq(map->grid_cart[1][0].y, 0);
	cr_assert_eq(map->grid_cart[1][0].z, 2);
	free_map(&map);
}

Test(test_parsing, parse_map_two_by_two)
{
	t_map *map = parse_map("assets/dummy_map_two_by_two");

	cr_assert_not_null(map);
	cr_assert_eq(map->grid_cart[0][0].z, 0);
	cr_assert_eq(map->grid_cart[1][0].z, 1);
	cr_assert_eq(map->grid_cart[0][1].z, 2);
	cr_assert_eq(map->grid_cart[1][1].z, 3);

	cr_assert_eq(map->grid_cart[0][0].x, 0);
	cr_assert_eq(map->grid_cart[1][0].x, 1);
	cr_assert_eq(map->grid_cart[0][1].x, 0);
	cr_assert_eq(map->grid_cart[1][1].x, 1);

	cr_assert_eq(map->grid_cart[0][0].y, 0);
	cr_assert_eq(map->grid_cart[1][0].y, 0);
	cr_assert_eq(map->grid_cart[0][1].y, 1);
	cr_assert_eq(map->grid_cart[1][1].y, 1);

	cr_assert_eq(map->width, 2);
	cr_assert_eq(map->height, 2);
	free_map(&map);
}