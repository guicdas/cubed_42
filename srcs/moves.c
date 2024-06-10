/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:44:24 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/10 19:03:34 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	check_move(int i, int j)
{
	if (d()->map[((int)d()->player_y + j) / 64] \
	[(((int)d()->player_x + i) / 64)] != 49)
		return (1);
	return (0);
}

void	rotate(int keypress)
{
	double	old_dir;
	double	old_plane;
	float	rot;

	rot = d()->player_a;
	old_dir = d()->player_dx;
	old_plane = d()->plane_x;
	if (keypress == KEY_A || keypress == KEY_LEFT)
		rot *= -1;
	d()->player_dx = (d()->player_dx * cos(rot)) - (d()->player_dy * sin(rot));
	d()->player_dy = (old_dir * sin(rot)) + (d()->player_dy * cos(rot));
	d()->plane_x = (d()->plane_x * cos(rot)) - (d()->plane_y * sin(rot));
	d()->plane_y = (old_plane * sin(rot)) + (d()->plane_y * cos(rot));
	d()->moves++;
}

void	move(int keypress)
{
	if (keypress == KEY_W)
	{
		if (check_move(d()->player_dx, d()->player_dy) == 1)
		{
			d()->player_x += d()->player_dx * d()->player_speed;
			d()->player_y += d()->player_dy * d()->player_speed;
			d()->moves++;
		}
	}
	else
	{
		if (check_move(-d()->player_dx, -d()->player_dy) == 1)
		{
			d()->player_x -= d()->player_dx * d()->player_speed;
			d()->player_y -= d()->player_dy * d()->player_speed;
			d()->moves++;
		}
	}
}
