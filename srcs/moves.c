/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:44:24 by gcatarin          #+#    #+#             */
/*   Updated: 2025/05/01 19:25:04 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static int	check_move(float i, float j)
{
	int	y;
	int	x;

	y = (int)(d()->player_y + j) / 64;
	x = (int)(d()->player_x + i) / 64;
	if (d()->map[y][x] != '1')
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
	if (keypress == KEY_LEFT)
		rot *= -1;
	d()->player_dx = (d()->player_dx * cos(rot)) - (d()->player_dy * sin(rot));
	d()->player_dy = (old_dir * sin(rot)) + (d()->player_dy * cos(rot));
	d()->plane_x = (d()->plane_x * cos(rot)) - (d()->plane_y * sin(rot));
	d()->plane_y = (old_plane * sin(rot)) + (d()->plane_y * cos(rot));
	d()->moves++;
}

void	move(int key)
{
	int	dir;

	dir = -1;
	if (key == KEY_W)
		dir = 1;
	if (check_move((dir * d()->player_dx) * d()->p_speed, 0) == 1)
		d()->player_x += dir * (d()->player_dx * d()->p_speed);
	if (check_move(0, (dir * d()->player_dy) * d()->p_speed) == 1)
		d()->player_y += dir * (d()->player_dy * d()->p_speed);
	d()->moves++;
}

void	move_sideways(int key)
{
	int	rot, dir;
	double x_movement;
	double y_movement;

	if (key != KEY_A)
		dir = 1;
	else
		dir = -1;
	rot = d()->player_a * (float) dir;
	x_movement = d()->player_dx * cos(rot - PI / 2);
	y_movement = d()->player_dy * sin(rot - PI / 2);
	
	if (check_move((dir * (x_movement - y_movement)) * d()->p_speed, 0) == 1)
		d()->player_x += dir * ((x_movement - y_movement) * d()->p_speed);
	if (check_move(0, dir * (x_movement + y_movement) * d()->p_speed) == 1)
		d()->player_y += ((d()->player_dx * sin(rot - PI / 2)) + \
		(d()->player_dy * cos(rot - PI / 2))) * d()->p_speed;

	d()->moves++;
}
