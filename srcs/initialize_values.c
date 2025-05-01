/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:10:24 by gcatarin          #+#    #+#             */
/*   Updated: 2025/05/01 22:42:26 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	init_image(t_img *img, char *path, int i)
{
	init_texture(img);
	if (i == 0)
		img->image = mlx_xpm_file_to_image(d()->mlx, \
path,&d()->texture_w, &d()->texture_h);
	else
		img->image = mlx_xpm_file_to_image(d()->mlx, \
path, &d()->mmap_s_w, &d()->mmap_s_h);
	if (img->image == NULL)
		error("Error\nCouldn't open map file!");
	if (i == 1 && (d()->mmap_s_w != MINISIZE || d()->mmap_s_h != MINISIZE))
		error("Error\nWrong minimap texture size\n");
	if (i == 0 && (d()->texture_w != TEXTURE_SIZE || \
	d()->texture_h != TEXTURE_SIZE))
		error("Error\nWrong texture size\n");
	img->addr = (int *)mlx_get_data_addr(img->image, &img->bpp, \
&img->linesize, &img->endian);
	if (img->addr == NULL)
		error("Error\nget_data_addr didn't work correctly!");
}

void	init_dda(int x)
{
	d()->camera_x = 2 * x / (double)SCREENW - 1;
	d()->ray_dir_x = (d()->player_dx / d()->p_speed) + \
d()->plane_x * d()->camera_x;
	d()->ray_dir_y = (d()->player_dy / d()->p_speed) + \
d()->plane_y * d()->camera_x;
	d()->map_x = (int)d()->player_x / 64;
	d()->map_y = (int)d()->player_y / 64;
	d()->delta_dist_x = fabs(1 / d()->ray_dir_x);
	d()->delta_dist_y = fabs(1 / d()->ray_dir_y);
}

void	initialize_data(void)
{
	d()->file_header[0].key = "NO";
	d()->file_header[0].target = &d()->map_no;
	d()->file_header[1].key = "SO";
	d()->file_header[1].target = &d()->map_so;
	d()->file_header[2].key = "WE";
	d()->file_header[2].target = &d()->map_we;
	d()->file_header[3].key = "EA";
	d()->file_header[3].target = &d()->map_ea;
	d()->file_header[4].key = "F";
	d()->file_header[4].target = &d()->map_f;
	d()->file_header[5].key = "C";
	d()->file_header[5].target = &d()->map_c;
	d()->settings_flag = -1;
	d()->p_speed = PLAYER_SPEED;
	// d()->last_mouse_x = SCREENW / 2;

	d()->texture_w = TEXTURE_SIZE;
	d()->texture_h = TEXTURE_SIZE;
	d()->mmap_s_w = MINISIZE;
	d()->mmap_s_h = MINISIZE;
}

static void	init_pixels(void)
{
	int		i;

	i = 0;
	if (d()->pixels)
		free_double((void **)d()->pixels);
	d()->pixels = (int **)ft_calloc(SCREENH + 1, sizeof(int *));
	if (!d()->pixels)
		error("Error\n Couldn't allocate pixels!");
	while (i < SCREENH)
	{
		d()->pixels[i] = ft_calloc(SCREENW + 1, sizeof(int));
		if (!d()->pixels[i])
			error("Error\n Couldn't allocate pixels!");
		i++;
	}
}

void	init_values(void)
{
	init_pixels();
	// take out init_pixels for cool effect
	// also not best for optimization
	d()->side_dist_x = 0;
	d()->side_dist_y = 0;
	d()->line_height = 0;
	d()->delta_dist_x = 0;
	d()->delta_dist_y = 0;
	d()->draw_start = 0;
	d()->draw_end = 0;
	d()->wall_dist = 0;
}
