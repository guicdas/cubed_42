/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:44:24 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/08 19:33:54 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static int	check_move(int i, int j)
{
	if (d()->map[((int)d()->player_y + j) / 64] \
		[(((int)d()->player_x + i ) / 64)] != 49)
		return (1);
	return (0);
}

int	move(int keypress)
{
	if (keypress == KEY_ESC)
		error("Leaving!\n");
	else if (keypress == KEY_A)
	{
		d()->player_a -= 0.1;
		if (d()->player_a < 0)
			d()->player_a += 2 * PI;
		d()->player_dx = cos(d()->player_a) * d()->player_speed;
		d()->player_dy = sin(d()->player_a) * d()->player_speed;
	}
	else if (keypress == KEY_W && \
	check_move(d()->player_dx, d()->player_dy) == 1)
	{
		d()->player_x += d()->player_dx;
		d()->player_y += d()->player_dy;
	}
	else if (keypress == KEY_D)
	{
		d()->player_a += 0.1;
		if (d()->player_a > 2 * PI)
			d()->player_a -= 2 * PI;
		d()->player_dx = cos(d()->player_a) * d()->player_speed;
		d()->player_dy = sin(d()->player_a) * d()->player_speed;
	}
	else if (keypress == KEY_S && \
	check_move(-d()->player_dx, -d()->player_dy) == 1)
	{
		d()->player_x -= d()->player_dx;
		d()->player_y -= d()->player_dy;
	}
	return (0);
}
