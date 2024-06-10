/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnuncio- <jnuncio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:01:48 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/10 21:01:32 by jnuncio-         ###   ########.fr       */
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
	init_pixels();
	d()->side_dist_x = 0;
	d()->side_dist_y = 0;
	d()->line_height = 0;
	d()->delta_dist_x = 0;
	d()->delta_dist_y = 0;
	d()->draw_start = 0;
	d()->draw_end = 0;
	d()->wall_dist = 0;
}

static void	show_settings(void)
{
	mlx_string_put(d()->mlx, d()->win_ptr, 2, 12, \
	RED, ft_itoa(d()->moves, 10, DECA));
	mlx_string_put(d()->mlx, d()->win_ptr, 2, 24, WHITE, "X:");
	mlx_string_put(d()->mlx, d()->win_ptr, 14, 26, \
	RED, ft_itoa(d()->player_x, 10, DECA));
	mlx_string_put(d()->mlx, d()->win_ptr, 40, 24, WHITE, "Y:");
	mlx_string_put(d()->mlx, d()->win_ptr, 54, 26, \
	RED, ft_itoa(d()->player_y, 10, DECA));
}

int	movekey_hook(int keypress)
{
	init_values();
	move(keypress);
	raycaster();
	render_frame();
	print_minimap();
	mlx_string_put(d()->mlx, d()->win_ptr, 2, 12, \
	RED, ft_itoa(d()->frames++, 10, DECA));
	return (0);
}
