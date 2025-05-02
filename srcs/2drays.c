/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2drays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:48:17 by gcatarin          #+#    #+#             */
/*   Updated: 2025/05/02 03:41:54 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static void	put_image(void *img, int h, int w)
{
	mlx_put_image_to_window(d()->mlx, d()->win_ptr, img, h, w);
}

static void	draw_player_direction(int x1, int y1, int color)
{
	float	i;
	int		px;
	int		py;

	i = 5;
	while (i > 0)
	{
		px = (x1 + d()->player_dx * i);
		py = (y1 + d()->player_dy * i);
		mlx_pixel_put(d()->mlx, d()->win_ptr, px, py, color);
		i -= 0.3;
	}
}

void draw_minimap(void)
{
	int	map_x;
	int	map_y;
	int	dy;
	int	dx;

	dy = -8;
	while (dy <= 5)
	{
		dx = -8;
		while (dx <= 5)
		{
			map_x = d()->player_x_map + dx;
			map_y = d()->player_y_map + dy;

			if (map_y < 0 || map_y >= d()->map_h + 1 || \
map_x < 0 || map_x >= (int)ft_strlen(d()->map[map_y]))
				continue;

			if (d()->map[map_y][map_x] == '1')
				put_image(d()->wall.image, (dx + 8) * 16, (dy + 8) * 16);
			else if (d()->map[map_y][map_x] == '-')
				put_image(d()->floor.image, (dx + 8) * 16, (dy + 8) * 16);
			else
				put_image(d()->door.image, (dx + 8) * 16, (dy + 8) * 16);
			dx++;
		}
		dy++;
	}
	mlx_pixel_put(d()->mlx, d()->win_ptr, 8 * 16 + 8, 8 * 16 + 8, GREEN);
	draw_player_direction(8 * 16 + 8, 8 * 16 + 8, RED);
}

void	print_settings(void)
{
	int	map_x;
	int map_y;
	char *info;

	map_x = 256 / 2;
	map_y = 196 / 2;
	draw_minimap();	 // if old moves...
	info = ft_itoa(d()->moves, 10, DECA);
	mlx_string_put(d()->mlx, d()->win_ptr, 2, 12, BLACK, info);
	mlx_string_put(d()->mlx, d()->win_ptr, 2, 24, WHITE, "Y:");
	info = ft_itoa((int)d()->player_y / 64, 10, DECA);
	mlx_string_put(d()->mlx, d()->win_ptr, 14, 26, BLACK, info);
	mlx_string_put(d()->mlx, d()->win_ptr, 40, 24, WHITE, "X:");
	info = ft_itoa((int)d()->player_x / 64, 10, DECA);
	mlx_string_put(d()->mlx, d()->win_ptr, 54, 26, BLACK, info);
}
