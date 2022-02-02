/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:21:45 by                   #+#    #+#             */
/*   Updated: 2022/02/01 18:21:45 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdF.h"
#include <stdio.h>

void	handle_linear_key_events(int keycode, t_data *img)
{
	if (keycode == 45)
		img->z_scale += 0.1f;
	else if (keycode == 61)
		img->z_scale -= 0.1f;
	else if (keycode == 65362)
		img->y_offset += 0.1f;
	else if (keycode == 65364)
		img->y_offset -= 0.1f;
	else if (keycode == 65361)
		img->x_offset += 0.1f;
	else if (keycode == 65363)
		img->x_offset -= 0.1f;
	else if (keycode == 46)
		img->zoom += 0.1f;
	else if (keycode == 44)
		img->zoom -= 0.1f;
	render_frame(img);
}

void	handle_rotation_key_events(int keycode, t_data *img)
{
	if (keycode == 65433)
		img->orientation = multiply(&img->orientation, euler2rot(0, 5, 0));
	else if (keycode == 65431)
		img->orientation = multiply(&img->orientation, euler2rot(0, -5, 0));
	else if (keycode == 65430)
		img->orientation = multiply(&img->orientation, euler2rot(-5, 0, 0));
	else if (keycode == 65432)
		img->orientation = multiply(&img->orientation, euler2rot(5, 0, 0));
	else if (keycode == 65437)
		img->orientation = multiply(&img->orientation, euler2rot(0, 0, -5));
	else if (keycode == 65438)
		img->orientation = multiply(&img->orientation, euler2rot(0, 0, 5));
}

int	key_handler(int keycode, t_data *img)
{
	printf("key : %d\n", keycode);
	if (keycode == 65307 || keycode == 38)
		tear_down_mlx_session(img);
	handle_rotation_key_events(keycode, img);
	handle_linear_key_events(keycode, img);
	return (0);
}
