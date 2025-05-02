/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:02:57 by gcatarin          #+#    #+#             */
/*   Updated: 2025/05/02 01:12:12 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static void	set_pixel(int x, t_img *img, int y)
{
	int		pixel;

	pixel = y * (img->linesize / 4) + x;
	if (d()->pixels[y][x] > 0)
		img->addr[pixel] = d()->pixels[y][x];
	else if (y < SCREENH / 2)
		img->addr[pixel] = d()->hex_ceiling;
	else if (y < SCREENH - 1)
		img->addr[pixel] = d()->hex_floor;
}

void	render_frame(void)
{
	t_img	img;
	int		x;
	int		y;

	img.image = mlx_new_image(d()->mlx, SCREENW, SCREENH);
	if (img.image == NULL)
		error("mlx rendering error\n");
	img.addr = (int *)mlx_get_data_addr(img.image, &img.bpp, \
&img.linesize, &img.endian);
	y = 0;
	while (y < SCREENH)
	{
		x = 0;
		while (x < SCREENW)
			set_pixel(x++, &img, y);
		y++;
	}
	mlx_put_image_to_window(d()->mlx, d()->win_ptr, img.image, 0, 0);
	mlx_destroy_image(d()->mlx, img.image);
	if (d()->settings_flag)
		print_settings();
}
