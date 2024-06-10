/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnuncio- <jnuncio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:10:24 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/10 20:17:26 by jnuncio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	init_img(char *path)
{
	int	*tmp;

	d()->img.image = NULL;
	d()->img.addr = NULL;
	tmp = mlx_xpm_file_to_image(d()->mlx, path, &d()->texture_size, \
		&d()->texture_size);
	if (tmp == NULL)
		error("Error\nXpm_to_img didn't work correctly!\n");
	d()->img.image = tmp;
	d()->img.bpp = 0;
	d()->img.linesize = 0;
	d()->img.endian = 0;
	tmp = (int *)mlx_get_data_addr(d()->img.image, &d()->img.bpp, \
		&d()->img.linesize, &d()->img.endian);
	if (tmp == NULL)
		error("Error\nget_data_addr didn't work correctly!\n");
	d()->img.addr = tmp;
}

void	init_values(void)
{
	d()->side_dist_x = 0;
	d()->side_dist_y = 0;
	d()->line_height = 0;
	d()->delta_dist_x = 0;
	d()->delta_dist_y = 0;
	d()->draw_start = 0;
	d()->draw_end = 0;
}
	/*pode ser usado para poderes no bonus
	->d()->planeX;
	->d()->planeY;
	->d()->player_speed;
	*/

void	init_pixels(void)
{
	int	i;
	int	**tmp;

	i = 0;
	tmp = ft_calloc(d()->screen_height + 1, sizeof(int *));
	if (!tmp)
		error("error!\n Couldn't allocate pixels\n");
	d()->pixels = tmp;
	while (i < SCREENH)
	{
		tmp[i] = ft_calloc(d()->screen_width + 1, sizeof(int));
		if (!tmp[i])
			error("error!\n Couldn't allocate pixels\n");
		d()->pixels[i] = tmp[i];
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
