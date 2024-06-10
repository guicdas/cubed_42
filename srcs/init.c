/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:10:24 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/10 19:02:05 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	init_image(t_img *img, char *path, int i)
{
	img->image = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->linesize = 0;
	img->endian = 0;

	if (i == 0)
		img->image = mlx_xpm_file_to_image(d()->mlx, path, &d()->texture_size, &d()->texture_size);
	else
		img->image = mlx_xpm_file_to_image(d()->mlx, path, &d()->mmap_s, &d()->mmap_s);
	if (img->image == NULL)
		{printf("%s\n", path);error("Error\nXpm_to_img didn't work correctly!\n");}
	
	img->addr = (int *)mlx_get_data_addr(img->image, &img->bpp, &img->linesize, &img->endian);
	if (img->addr == NULL)
		error("Error\nget_data_addr didn't work correctly!\n");
}

void	init_pixels(void)
{
	int	i;

	i = 0;
	if (d()->pixels)
		free_double_int(d()->pixels);
	d()->pixels = ft_calloc(d()->screen_height + 1, sizeof(int *));
	if (!d()->pixels)
			error("Error\n Couldn't allocate pixels\n");
	while (i < d()->screen_height)
	{
		d()->pixels[i] = ft_calloc(d()->screen_width + 1, sizeof(int));
		if (!d()->pixels[i])
			error("Error\n Couldn't allocate pixels\n");
		i++;
	}	
}

void	init_dda(int x)
{
	d()->player_a = ROT_SPEED;
	d()->camera_x = 2 * x / (double)d()->screen_width - 1;
	d()->ray_dir_x = (d()->player_dx * d()->player_speed) + d()->plane_x * d()->camera_x;
	d()->ray_dir_y = (d()->player_dy * d()->player_speed) + d()->plane_y * d()->camera_x;
	d()->map_x = (int)d()->player_x / 64;
	d()->map_y = (int)d()->player_y / 64;
	d()->delta_dist_x = fabs(1 / d()->ray_dir_x);
	d()->delta_dist_y = fabs(1 / d()->ray_dir_y);
}

void	initialize_everything(void)
{
	int	i;

	i = 0;
	d()->mlx = NULL;
	d()->win_ptr = NULL;
	d()->moves = 0;
	d()->textures = NULL;
	d()->pixels = NULL;
	d()->texture_index = 0;
	d()->texture_size = TEXTURE_SIZE;
	d()->player_speed = PLAYER_SPEED;
	d()->screen_height = SCREENH;
	d()->screen_width = SCREENW;
	d()->mmap_s = MINISIZE;
	d()->plane_x = (double) 0;
	d()->plane_y = (double) 0.66;
	d()->max_x = 0;
	d()->map_x = 0;
	d()->map_y = 0;
}
