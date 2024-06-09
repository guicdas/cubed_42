/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2drays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:48:17 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/09 19:25:57 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	draw_map(void)
{
	int	y;
	int	x;

	y = 0;
	while (y < d()->map_h - 1)
	{
		x = 0;
		while (x <= d()->map_w - 1)
		{
			if (d()->map[y][x] == '1')
				mlx_put_image_to_window(d()->mlx, d()->win_ptr, \
				d()->wall.image, x * d()->minimap_size, y * d()->minimap_size);
			else 
				mlx_put_image_to_window(d()->mlx, d()->win_ptr, \
				d()->empty.image, x * d()->minimap_size, y * d()->minimap_size);
			x++;
		}
		y++;
	}
}

float	distance(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	draw_player_direction(int x1, int y1, int color)
{
	float	i;

	i = 7;
	while (i > 0)
	{
		mlx_pixel_put(d()->mlx, d()->win_ptr, \
		(x1 + d()->player_dx * i), (y1 + d()->player_dy * i), color);
		i -= 0.2;
	}
}

void	draw_horizontal_rays(void)
{
	
}/*
	int m, p, dof;
	float ray_x, ray_y, yo, dH =10000, hx=d()->player_x, hy=d()->player_y;
	float ray_a = d()->player_a - DR*30; 
	if (ray_a < 0)
		ray_a += 2 * PI;
	if (ray_a < 2 * PI)
		ray_a -= 2 * PI;

	for(int r = 0 ; r < 1 ; r++)
	{
		dof = 0;
		yo = 8;
		if (d()->player_a > PI)
		{
			ray_y = ((int)d()->player_y >> 6)*64 - 0.0001;
			ray_x = (d()->player_y - ray_y) * -1 /tan(d()->player_a) + d()->player_x;
			yo *= -1;
		}
		else if (d()->player_a < PI)
		{
			ray_y = ((int)d()->player_y >> 6)*64 + 64;
			ray_x = (d()->player_y - ray_y) * -1 /tan(d()->player_a) + d()->player_x;
		}
		else if (d()->player_a == 0 || d()->player_a == PI)
		{
			ray_x = d()->player_x;
			ray_y = d()->player_y;
			dof = 8;
		}
		while (dof < 16)
		{
			m = (int) (ray_y) >> 6;
			p = (int) (ray_x) >> 6;
			printf("dof: %d, x: %d, y: %d\n", dof, m, p);
			if (m < d()->map_x - 2 && p < d()->map_y - 2 && m > 0 && p > 0)
			{
				if 	(d()->map[m][p] == '1')
				{
					hx = ray_x; hy = ray_y;
					dH = distance(d()->player_x, d()->player_y, hx, hy);
					dof = 16;
				}
				else
				{	
					ray_x += -yo * -1 /tan(d()->player_a);
					ray_y += yo;
					dof += 1;
				}
			}
			else
			{
				ray_x += -yo * -1 /tan(d()->player_a);
				ray_y += yo;
				dof += 1;
				
			}
		draw_player_direction(ray_x, ray_y, 0x228B22);
		}
		printf("\n");
		draw_player_direction(ray_x, ray_y, 0xFFFF00);
		ray_a += DR;
		if (ray_a < 0)
			ray_a += 2 * PI;
		if (ray_a < 2 * PI)
			ray_a -= 2 * PI;
		}
		dof = 0;
		yo = 8;
		float dV =10000, vx=d()->player_x, vy=d()->player_y;
		if (d()->player_a > (PI/2) && d()->player_a < (3*PI/2))
		{
			ray_x = ((int)d()->player_x >> 6)*64 - 0.0001;
			ray_y = (d()->player_x - ray_x) * -tan(d()->player_a) + d()->player_y;
			yo = -8;
		}
		else if (d()->player_a < (PI/2) || d()->player_a > (3*PI/2))
		{
			ray_x = ((int)d()->player_x >> 6)*64 + 64;
			ray_y = (d()->player_x - ray_x) * -tan(d()->player_a) + d()->player_y;
		}
		else if (d()->player_a == 0 || d()->player_a == PI)
		{
			ray_x = d()->player_x;
			ray_y = d()->player_y;
			dof = 8;
		}
		while (dof < 8)
		{
			m = (int) (ray_y) >> 6;
			p = (int) (ray_x) >> 6;
			if (m < d()->map_x - 2 && p < d()->map_y - 2 && m > 0 && p > 0)
			{
				if 	(d()->map[m][p] == '1')
				{
					vx = ray_x; vy = ray_y;
					dV = distance(d()->player_x, d()->player_y, vx, vy);
					dof = 8;
				}
				else
				{	
					ray_x += yo;
					ray_y += -yo * -tan(d()->player_a);
					dof += 1;
				}
			}
			else
			{
				ray_x += yo;
				ray_y += -yo * -tan(d()->player_a);
				dof += 1;
				
			}
		}
		if (dV < dH)
		{
			ray_x = vx;
			ray_x = vx;
		}
		if (dV > dH)
		{
			ray_x = hx;
			ray_x = hx;
		}
		draw_player_direction(ray_x, ray_y, 0xFFA500);
		*/