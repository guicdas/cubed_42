/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2drays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnuncio- <jnuncio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:48:17 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/13 12:01:46 by jnuncio-         ###   ########.fr       */
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
	while (d()->map[y])
	{
		x = 0;
		while (x < d()->max_x)
		{
			if (x < ft_strlen(d()->map[y]))
			{
				if (d()->map[y][x] == '1')
					put_image(d()->wall.image, \
					x * d()->mmap_s_w, y * d()->mmap_s_h);
				else if (d()->map[y][x] == '-' || d()->map[y][x] == 'P' \
				|| d()->map[y][x] == '0')
					put_image(d()->floor.image, \
					x * d()->mmap_s_w, y * d()->mmap_s_h);
			}
			x++;
		}
		y++;
	}
}

void	draw_player_direction(int x1, int y1, int color)
{
	float	i;

	i = 5;
	while (i > 0)
	{
		mlx_pixel_put(d()->mlx, d()->win_ptr, \
		(x1 + d()->player_dx * i), (y1 + d()->player_dy * i), color);
		i -= 0.2;
	}
}
