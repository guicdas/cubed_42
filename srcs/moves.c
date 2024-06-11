/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:44:24 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/11 21:47:19 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	check_move(float i, float j)
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

void	move(int keypress)
{
	if (keypress == KEY_W)
	{
		if (check_move(d()->player_dx * d()->player_speed, 0) == 1)
			d()->player_x += d()->player_dx * d()->player_speed;
		if (check_move(0, d()->player_dy * d()->player_speed) == 1)
			d()->player_y += d()->player_dy * d()->player_speed;
		d()->moves++;
	}
	else
	{
		if (check_move(-d()->player_dx * d()->player_speed, 0) == 1)
			d()->player_x -= d()->player_dx * d()->player_speed;
		if (check_move(0, -d()->player_dy * d()->player_speed) == 1)
			d()->player_y -= d()->player_dy * d()->player_speed;
		d()->moves++;
	}
}

void	move_left(void)
{
	int	rot;

	rot = d()->player_a;
	if (check_move(((d()->player_dx * cos(rot - PI / 2)) - \
	(d()->player_dy * sin(rot - PI / 2))) * d()->player_speed, 0) == 1)
		d()->player_x += ((d()->player_dx * cos(rot - PI / 2)) - \
		(d()->player_dy * sin(rot - PI / 2))) * d()->player_speed;
	if (check_move(0, ((d()->player_dx * sin(rot - PI / 2)) + \
	(d()->player_dy * cos(rot - PI / 2))) * d()->player_speed) == 1)
		d()->player_y += ((d()->player_dx * sin(rot - PI / 2)) + \
		(d()->player_dy * cos(rot - PI / 2))) * d()->player_speed;
	d()->moves++;
}

void	move_right(void)
{
	int	rot;

	rot = d()->player_a;
	if (check_move(-((d()->player_dx * cos(-rot - PI / 2)) - \
	(d()->player_dy * sin(-rot - PI / 2))) * d()->player_speed, 0) == 1)
		d()->player_x -= ((d()->player_dx * cos(-rot - PI / 2)) - \
		(d()->player_dy * sin(-rot - PI / 2))) * d()->player_speed;
	if (check_move(0, -((d()->player_dx * sin(-rot - PI / 2)) + \
	(d()->player_dy * cos(-rot - PI / 2))) * d()->player_speed) == 1)
		d()->player_y -= ((d()->player_dx * sin(-rot - PI / 2)) + \
		(d()->player_dy * cos(-rot - PI / 2))) * d()->player_speed;
	d()->moves++;
}
