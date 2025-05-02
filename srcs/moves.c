/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:44:24 by gcatarin          #+#    #+#             */
/*   Updated: 2025/05/02 02:25:31 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static int	check_move(float i, float j)
{
	int	y;
	int	x;

	y = (int)(d()->player_y + j) / 64;
	x = (int)(d()->player_x + i) / 64; // texture size ou assim
	if (d()->map[y][x] != '1')
		return (1);
	return (0);
}

void	rotate(int keypress)
{
	double	old_dir;
	double	old_plane;
	double	rot;

	rot = d()->player_a;
	old_dir = d()->player_dx;
	old_plane = d()->plane_x;
	rot *= -2 * (keypress == KEY_LEFT) + 1;
	//printf(" %f - %f\n",  rot, d()->player_a);
	d()->player_dx = (d()->player_dx * cos(rot)) - (d()->player_dy * sin(rot));
	d()->player_dy = (old_dir * sin(rot)) + (d()->player_dy * cos(rot));
	d()->plane_x = (d()->plane_x * cos(rot)) - (d()->plane_y * sin(rot));
	d()->plane_y = (old_plane * sin(rot)) + (d()->plane_y * cos(rot));
	d()->moves++;
}

void	move(int key)
{
	int	dir;

	dir = -2 * (key != KEY_W) + 1;
	if (check_move((dir * d()->player_dx) * d()->p_speed, 0) == 1)
	{
		d()->player_x += dir * (d()->player_dx * d()->p_speed);
		d()->player_x_map = (d()->player_x - 32) / 64;
	}
	if (check_move(0, (dir * d()->player_dy) * d()->p_speed) == 1)
	{
		d()->player_y += dir * (d()->player_dy * d()->p_speed);
		d()->player_y_map = (d()->player_y - 32) / 64;
	}
	d()->moves++;
}

void	move_sideways(int key)
{
	int	dir;

	dir = -2 * (key != KEY_D) + 1;
	if (check_move(dir * -d()->player_dy * d()->p_speed, 0) == 1)
	{
		d()->player_x += dir * -d()->player_dy * d()->p_speed;
		d()->player_x_map = (d()->player_x - 32) / 64;
	}
	if (check_move(0, dir * d()->player_dx * d()->p_speed) == 1)
	{
		d()->player_y += dir * d()->player_dx * d()->p_speed;
		d()->player_y_map = (d()->player_y - 32) / 64;
	}
	d()->moves++;
}
