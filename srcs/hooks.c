/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:01:48 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/08 19:16:57 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	print_minimap(void)
{
	draw_map();
	mlx_pixel_put(d()->mlx, d()->win_ptr, d()->player_x, d()->player_y, GREEN);
	draw_player_direction(d()->player_x, d()->player_y, RED);
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
