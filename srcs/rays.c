/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:57:42 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/11 15:02:35 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static void	calculate_dda(void)
{
	if (d()->ray_dir_x < 0)
	{
		d()->step_x = -1;
		d()->side_dist_x = ((d()->player_x / 64) - d()->map_x) \
		* d()->delta_dist_x;
	}
	else
	{
		d()->step_x = 1;
		d()->side_dist_x = (d()->map_x + 1.0 - (d()->player_y / 64)) \
		* d()->delta_dist_x;
	}
	if (d()->ray_dir_y < 0)
	{
		d()->step_y = -1;
		d()->side_dist_y = ((d()->player_y / 64) - d()->map_y) \
		* d()->delta_dist_y;
	}
	else
	{
		d()->step_y = 1;
		d()->side_dist_y = (d()->map_y + 1.0 - (d()->player_y / 64)) \
		* d()->delta_dist_y;
	}
}

static void	dda_execute(void)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (d()->side_dist_x < d()->side_dist_y)
		{
			d()->side_dist_x += d()->delta_dist_x;
			d()->map_x += d()->step_x;
			d()->side = 0;
		}
		else
		{
			d()->side_dist_y += d()->delta_dist_y;
			d()->map_y += d()->step_y;
			d()->side = 1;
		}
		if (d()->map_y < 0.25 || d()->map_x < 0.25 || \
		d()->map_x > d()->screen_width - 0.25 \
		|| d()->map_y > d()->screen_height - 1.25)
			break ;
		else if (d()->map[d()->map_y][d()->map_x] == '1')
			hit = 1;
	}
}

static void	calculate_line(void)
{
	if (d()->side == 0)
		d()->wall_dist = (d()->side_dist_x - d()->delta_dist_x);
	else
		d()->wall_dist = (d()->side_dist_y - d()->delta_dist_y);
	d()->line_height = (int)(d()->screen_height / d()->wall_dist);
	d()->draw_start = -(d()->line_height) / 2 + (d()->screen_height / 2);
	if (d()->draw_start < 0)
		d()->draw_start = 0;
	d()->draw_end = d()->line_height / 2 + (d()->screen_height / 2);
	if (d()->draw_end >= d()->screen_height)
		d()->draw_end = d()->screen_height - 1;
	if (d()->side == 0)
		d()->wall_x = d()->player_y + d()->wall_dist * d()->ray_dir_y;
	else
		d()->wall_x = d()->player_x + d()->wall_dist * d()->ray_dir_x;
	d()->wall_x -= floor(d()->wall_x);
}

void	update_textures(int x)
{
	int	color;
	int	y;

	get_index();
	d()->texture_x = (int)(d()->wall_x * d()->texture_size);
	if ((d()->side == 0 && d()->ray_dir_x > 0) || \
	(d()->side == 1 && d()->ray_dir_y < 0))
		d()->texture_x = d()->texture_size - d()->texture_x - 1;
	d()->step = d()->texture_size / d()->line_height;
	d()->pos = (d()->draw_start - d()->screen_height / 2 + \
	d()->line_height / 2) * d()->step;
	y = d()->draw_start;
	while (y < d()->draw_end)
	{
		d()->texture_y = (int)d()->pos & (d()->texture_size - 1);
		d()->pos += d()->step;
		color = d()->textures[d()->texture_index][d()->texture_size \
		* d()->texture_y + d()->texture_x];
		if (d()->side == 1)
			color = (color >> 1) & 8355711;
		if (color > 0)
			d()->pixels[y][x] = color;
		y++;
	}
}

void	raycaster(void)
{
	int		i;

	i = 0;
	while (i < d()->screen_width)
	{
		init_dda(i);
		calculate_dda();
		dda_execute();
		calculate_line();
		update_textures(i);
		i++;
	}
}
