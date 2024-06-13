/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnuncio- <jnuncio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:10:24 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/13 12:09:07 by jnuncio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	init_image(t_img *img, char *path, int i)
{
	init_texture(img);
	if (i == 0)
	{
		img->image = mlx_xpm_file_to_image(d()->mlx, path, \
		&d()->texture_w, &d()->texture_h);
	}
	else
	{
		img->image = mlx_xpm_file_to_image(d()->mlx, path, \
		&d()->mmap_s_w, &d()->mmap_s_h);
	}
	if (img->image == NULL)
		error("Error\nCouldn't open map file!\n");
	if (i == 1 && (d()->mmap_s_w != MINISIZE || d()->mmap_s_h != MINISIZE))
		error("Error\nWrong minimap texture size\n");
	if (i == 0 && (d()->texture_w != TEXTURE_SIZE || \
	d()->texture_h != TEXTURE_SIZE))
		error("Error\nWrong texture size\n");
	img->addr = (int *)mlx_get_data_addr(img->image, &img->bpp, \
	&img->linesize, &img->endian);
	if (img->addr == NULL)
		error("Error\nget_data_addr didn't work correctly!\n");
}

void	init_dda(int x)
{
	d()->camera_x = 2 * x / (double)d()->screen_width - 1;
	d()->ray_dir_x = (d()->player_dx / d()->player_speed) \
	+ d()->plane_x * d()->camera_x;
	d()->ray_dir_y = (d()->player_dy / d()->player_speed) \
	+ d()->plane_y * d()->camera_x;
	d()->map_x = (int)d()->player_x / 64;
	d()->map_y = (int)d()->player_y / 64;
	d()->delta_dist_x = fabs(1 / d()->ray_dir_x);
	d()->delta_dist_y = fabs(1 / d()->ray_dir_y);
}

void	initialize_everything(void)
{
	d()->mlx = NULL;
	d()->win_ptr = NULL;
	d()->moves = 0;
	d()->textures = NULL;
	d()->pixels = NULL;
	d()->texture_index = 0;
	d()->texture_w = TEXTURE_SIZE;
	d()->texture_h = TEXTURE_SIZE;
	d()->player_speed = PLAYER_SPEED;
	d()->screen_height = SCREENH;
	d()->screen_width = SCREENW;
	d()->mmap_s_w = MINISIZE;
	d()->mmap_s_h = MINISIZE;
	d()->max_x = 0;
	d()->map_x = 0;
	d()->map_y = 0;
	d()->map_h = 0;
}

void	init_values(void)
{
	init_pixels();
	d()->side_dist_x = 0;
	d()->side_dist_y = 0;
	d()->line_height = 0;
	d()->delta_dist_x = 0;
	d()->delta_dist_y = 0;
	d()->draw_start = 0;
	d()->draw_end = 0;
	d()->wall_dist = 0;
}

void	init_pixels(void)
{
	int		i;
	void	*tmp;
	void	*tmp1;

	i = 0;
	if (d()->pixels)
		free_double((void **)d()->pixels);
	tmp = ft_calloc(d()->screen_height + 1, sizeof(int *));
	d()->pixels = tmp;
	if (!d()->pixels)
		error("Error\n Couldn't allocate pixels\n");
	while (i < d()->screen_height)
	{
		tmp1 = ft_calloc(d()->screen_width + 1, sizeof(int));
		d()->pixels[i] = tmp1;
		if (!d()->pixels[i])
			error("Error\n Couldn't allocate pixels\n");
		i++;
	}
}
