/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:10:24 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/08 19:55:32 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	init_img(char *path){
	d()->img.image = NULL;
	d()->img.addr = NULL;
	d()->img.image = mlx_xpm_file_to_image(d()->mlx, path, &d()->texture_size, &d()->texture_size);
	if (d()->img.image == NULL)
		error("Error\nXpm_to_img didn't work correctly!\n");

	d()->img.bpp = 0;
	d()->img.linesize = 0;
	d()->img.endian = 0;
	
	d()->img.addr = (int *)mlx_get_data_addr(d()->img.image, &d()->img.bpp, &d()->img.linesize, &d()->img.endian);
	if (d()->img.addr == NULL)
		error("Error\nget_data_addr didn't work correctly!\n");
}

void	init_values(){
	d()->side_dist_x = 0;
	d()->side_dist_y = 0;
	d()->line_height = 0;
	d()->delta_dist_x = 0;
	d()->delta_dist_y = 0;
	d()->draw_start = 0;
	d()->draw_end = 0;

	/*pode ser usado para poderes no bonus
	->d()->planeX;
	->d()->planeY;
	->d()->player_speed;
	*/
}

void	init_pixels(){
	int	i;

	i = 0;
	d()->pixels = ft_calloc(d()->screen_height + 1, sizeof(int *));
	if (!d()->pixels)
			error("error!\n Couldn't allocate pixels\n");
	while (i < SCREENH)
	{
		d()->pixels[i] = ft_calloc(d()->screen_width + 1, sizeof(int));
		if (!d()->pixels[i])
			error("error!\n Couldn't allocate pixels\n");
		i++;
	}	
}

void	init_dda(int x)
{
	d()->camera_x = 2 * x / (double)d()->screen_width - 1;
	d()->ray_dir_x = d()->player_dx + d()->plane_x * d()->camera_x;
	d()->ray_dir_y = d()->player_dy + d()->plane_y * d()->camera_x;
	d()->map_x = (int)d()->player_x;
	d()->map_y = (int)d()->player_y;
	d()->delta_dist_x = fabs(1 / d()->ray_dir_x);
	d()->delta_dist_y = fabs(1 / d()->ray_dir_y);
}