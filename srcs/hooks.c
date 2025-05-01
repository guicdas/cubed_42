/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:01:48 by gcatarin          #+#    #+#             */
/*   Updated: 2025/05/01 20:31:15 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static void	show_settings(void)
{
	mlx_string_put(d()->mlx, d()->win_ptr, 2, 12, \
BLACK, ft_itoa(d()->moves, 10, DECA));
	mlx_string_put(d()->mlx, d()->win_ptr, 2, 24, WHITE, "Y:");
	mlx_string_put(d()->mlx, d()->win_ptr, 14, 26, \
BLACK, ft_itoa((int)d()->player_y / 64, 10, DECA));
	mlx_string_put(d()->mlx, d()->win_ptr, 40, 24, WHITE, "X:");
	mlx_string_put(d()->mlx, d()->win_ptr, 54, 26, \
BLACK, ft_itoa((int)d()->player_x / 64, 10, DECA));
}

static void	print_minimap(void)
{
	draw_map();
	mlx_pixel_put(d()->mlx, d()->win_ptr, \
(d()->player_x / 64) * d()->mmap_s_w, \
(d()->player_y / 64) * d()->mmap_s_h, GREEN);
	draw_player_direction((d()->player_x / 64) * d()->mmap_s_w, \
(d()->player_y / 64) * d()->mmap_s_h, RED);
	show_settings();
}

int	movekey_hook(int key)
{
	init_values();
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
	if (d()->settings_flag)
		print_minimap();
	return (0);
}

int	destroy_hook(void)
{
	leave();
	return (0);
}

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
}