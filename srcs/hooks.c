/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:01:48 by gcatarin          #+#    #+#             */
/*   Updated: 2025/05/02 02:29:24 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000L);
}

int	frame_count_hook(void)
{
	static int	frames = 0;
	static long	last_time = 0;
	static int	fps = 0;
	static int	old_moves = 0;
	long		now;

	now = get_time_ms();
	if (old_moves != d()->moves)
	{
		render_frame();
		old_moves = d()->moves;
	}
	if (now - last_time >= 1000)
	{
		fps = frames;
		frames = 0;
		last_time = now;
		printf("FPS: %d\n", fps);
	}
	return (0);
}

int	movekey_hook(int key)
{
	init_pixels_and_values();
	if (key == KEY_ESC)
		leave();
	d()->settings_flag = -2 * (key == KEY_Q) + 1;
	if (key == KEY_W || key == KEY_S)
		move(key);
	else if (key == KEY_A || key == KEY_D)
		move_sideways(key);
	else if (key == KEY_RIGHT || key == KEY_LEFT)
		rotate(key);
	raycaster();
	render_frame();
	if ((int)(d()->player_x - 32) / 64 != d()->player_x_map)
		error("DEumr\nerda!");
	return (0);
}

int	destroy_hook(void)
{
	leave();
	return (0);
}

/*
static void	wrap_mouse_position(int x, int y)
{
	int edge_warp;

	edge_warp = 20;
	if (x > SCREENW - edge_warp)
	{
		x = edge_warp;
		mlx_mouse_move(d()->mlx, d()->win_ptr, x, y);
	}
	if (x < edge_warp)
	{
		x = SCREENW - edge_warp;
		mlx_mouse_move(d()->mlx, d()->win_ptr, x, y);
	}
}

int mouse_move(int x, int y, void *p)
{
	(void) p;
	double	old_dir;
	double	old_plane;
	float	rot;

	rot = d()->player_a;
	old_dir = d()->player_dx;
	old_plane = d()->plane_x;
	wrap_mouse_position(x, y);

	//if (x == d()->last_mouse_x)
		return (0);
	//if (x < d()->last_mouse_x)
		rot *= -1;
	d()->player_dx = (d()->player_dx * cos(rot)) - (d()->player_dy * sin(rot));
	d()->player_dy = (old_dir * sin(rot)) + (d()->player_dy * cos(rot));
	d()->plane_x = (d()->plane_x * cos(rot)) - (d()->plane_y * sin(rot));
	d()->plane_y = (old_plane * sin(rot)) + (d()->plane_y * cos(rot));
	return (0);
}*/