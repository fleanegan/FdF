/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:44:09 by                   #+#    #+#             */
/*   Updated: 2022/02/01 17:41:27 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "get_next_line_bonus.h"
# include "math.h"
# include <fcntl.h>

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}		t_point;

typedef struct s_dimension_2d
{
	int	x_max;
	int	x_min;
	int	y_max;
	int	y_min;
}		t_dimension_2d;

typedef struct s_map
{
	t_point	**grid_cart;
	t_point	**grid_iso;
	int		width;
	int		height;
}		t_map;

typedef struct t_rotation_matrix
{
	double	mat[3][3];
	int		width;
	int		height;
}			t_rot_matrix;

typedef struct s_data {
	void				*img;
	char				*addr;
	void				*mlx;
	void				*mlx_win;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	t_dimension_2d		win_size;
	t_dimension_2d		object_size;
	t_rot_matrix		orientation;
	t_map				*map;
	float				z_scale;
}	t_data;

// parsing
t_map			*new_map(int width, int height);
void			init_view(t_data *img);
int				measure_map(const char *file_name, int *width, int *height);
t_map			*parse_map(const char *string);
int				parse_line(char *line, t_map *map, int y_act);

// transformation
float			calc_zoom_factor(t_dimension_2d *img, t_dimension_2d *screen);
void			apply_transformations_to_point(t_point *in, \
				t_point *out, t_rot_matrix rot_mat, float z_scale);
void			zoom_grid(t_map *map, \
				float xy_factor, float z_factor, t_point **grid);
void			apply_transformations_to_grid(t_map *map, \
				t_rot_matrix rot_mat, float z_scale);
void			move_grid(t_map *map, int x_off, int y_off, int z_off);

// drawing
void			turn_all_pixels_black(t_data *img);
void			draw_line(t_point p0, t_point p1, t_data *img);
void			draw_1px_to_img(t_data *data, int x, int y, int color);
void			draw_grid(t_map *map, t_data *img);

// matrix operations
void			zero_init_rotation_matrix(t_rot_matrix *t);
t_rot_matrix	euler2rot(double alpha_deg, double beta_deg, double gamma_deg);
t_rot_matrix	multiply(t_rot_matrix *a, t_rot_matrix b);
void			rotate_point(t_point *p, t_rot_matrix *mat);

// helper functions
void			print_coordinates(t_point *pt);
t_dimension_2d	measure_necessary_screen_space(t_map *map);
void			*free_map(t_map **map);
void			set_point(t_point *pt, double x, double y, double z);
t_rot_matrix	init_with_isometric_orientation(void);
t_point			**new_grid(t_map *map);

#endif //FDF_H
