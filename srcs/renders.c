/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:02:57 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/08 19:59:13 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static void	set_pixel(int x, int y)
{
	int	pixel;

	if (d()->pixels[y][x] > 0)
	{
		pixel = y * (d()->img.linesize / 4) + x;
		d()->img.addr[pixel] = d()->pixels[y][x];
	}
	else if (y < d()->screen_width / 2)
	{
		pixel = y * (d()->img.linesize / 4) + x;
		d()->img.addr[pixel] = d()->map_c;
	}
	else if (y < d()->screen_height - 1)
	{
		pixel = y * (d()->img.linesize / 4) + x;
		d()->img.addr[pixel] = d()->map_c;
	}
}

void	render_frame(void)
{
	int	x;
	int	y;

	d()->img.image = mlx_new_image(d()->mlx, d()->screen_width, d()->screen_height);
	if (d()->img.image == NULL)
		error("mlx rendering error\n");
	d()->img.addr = (int *)mlx_get_data_addr(d()->img.image, \
	&d()->img.bpp, &d()->img.linesize, &d()->img.endian);
	y = 0;
	while (y < d()->screen_height)
	{
		x = 0;
		while (x < d()->screen_width)
			set_pixel(x++, y);
		y++;
	}
	mlx_put_image_to_window(d()->mlx, d()->win_ptr, d()->img.image, 0, 0);
	mlx_destroy_image(d()->mlx, d()->img.image);
}
