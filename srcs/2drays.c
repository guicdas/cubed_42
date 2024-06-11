/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2drays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:48:17 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/11 15:05:08 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	put_image(void *img, int h, int w)
{
	mlx_put_image_to_window(d()->mlx, d()->win_ptr, img, h, w);
}

void	draw_map(void)
{
	int	y;
	int	x;

	y = 0;
	while (y < d()->map_h)
	{
		x = 0;
		while (x < d()->max_x)
		{
			if (x < ft_strlen(d()->map[y]))
			{
				if (d()->map[y][x] == '1')
					put_image(d()->wall.image, \
					x * d()->mmap_s, y * d()->mmap_s);
				else 
					put_image(d()->floor.image, \
					x * d()->mmap_s, y * d()->mmap_s);
			}
			else
				put_image(d()->empty.image, \
				x * d()->mmap_s, y * d()->mmap_s);
			x++;
		}
		y++;
	}
}
/*
void	draw_map(void)
{
	int	y;
	int	x;

	y = 0;
	while (y < d()->map_h - 1)
	{
		x = 0;
		while (x < d()->max_x)
		{
			if (x < ft_strlen(d()->map[y]))
			{
				if (d()->map[y][x] == '1')
					put_image(d()->wall.image, x * d()->mmap_s + \
					d()->player_x / 10, y * d()->mmap_s + d()->player_y / 10);
				else 
					put_image(d()->floor.image, x * d()->mmap_s + \
					d()->player_x / 10, y * d()->mmap_s + d()->player_y / 10);
			}
			else
				put_image(d()->empty.image, x * d()->mmap_s + \
				d()->player_x / 10, y * d()->mmap_s + d()->player_y / 10);
			x++;
		}
		y++;
	}
}*/

float	distance(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	draw_player_direction(int x1, int y1, int color)
{
	float	i;

	i = 7;
	while (i > 0)
	{
		mlx_pixel_put(d()->mlx, d()->win_ptr, \
		(x1 + d()->player_dx * i), (y1 + d()->player_dy * i), color);
		i -= 0.2;
	}
}
