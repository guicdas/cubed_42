/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:01:48 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/09 20:16:30 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	print_minimap(void)
{
	draw_map();
	mlx_pixel_put(d()->mlx, d()->win_ptr, d()->player_x / 2, \
	d()->player_y / 2, GREEN);
	draw_player_direction(d()->player_x / 2, d()->player_y / 2, RED);
}

void	init_values(void)
{
	// init_pixels();
	d()->side_dist_x = 0;
	d()->side_dist_y = 0;
	d()->line_height = 0;
	d()->delta_dist_x = 0;
	d()->delta_dist_y = 0;
	d()->draw_start = 0;
	d()->draw_end = 0;
}

int	movekey_hook(int keypress)
{
	int	key;

	init_values();
	if (keypress == KEY_ESC)
			error("Leaving!\n");
	key = move(keypress);
	raycaster();
	render_frame();
	// print_minimap();
	if (key == 1)
		d()->frames++;
	mlx_string_put(d()->mlx, d()->win_ptr, 2, 12, \
	RED, ft_itoa(d()->frames, 10, DECA));
	return (0);
}
