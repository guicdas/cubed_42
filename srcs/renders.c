/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:02:57 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/11 19:04:45 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static void	set_pixel(int x, t_img *img, int y)
{
	int		pixel;

	if (d()->pixels[y][x] > 0)
	{
		pixel = y * (img->linesize / 4) + x;
		img->addr[pixel] = d()->pixels[y][x];
	}
	else if (y < d()->screen_height / 2)
	{
		pixel = y * (img->linesize / 4) + x;
		img->addr[pixel] = d()->map_c;
	}
	else if (y < d()->screen_height - 1)
	{
		pixel = y * (img->linesize / 4) + x;
		img->addr[pixel] = d()->map_f;
	}
}

void	render_frame(void)
{
	t_img	img;
	int		x;
	int		y;

	img.image = mlx_new_image(d()->mlx, d()->screen_width, d()->screen_height);
	if (img.image == NULL)
		error("mlx rendering error\n");
	img.addr = (int *)mlx_get_data_addr(img.image, &img.bpp, \
	&img.linesize, &img.endian);
	y = 0;
	while (y < d()->screen_height)
	{
		x = 0;
		while (x < d()->screen_width)
			set_pixel(x++, &img, y);
		y++;
	}
	mlx_put_image_to_window(d()->mlx, d()->win_ptr, img.image, 0, 0);
	mlx_destroy_image(d()->mlx, img.image);
}
