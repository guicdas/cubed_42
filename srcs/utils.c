/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:32:04 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/10 19:11:09 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	if (n < 1)
		return ;
	while (n-- >= 1)
		((char *)s)[i++] = '\0';
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;
	size_t	total_mem;

	total_mem = nmemb * size;
	if (total_mem && (total_mem / size) != nmemb)
		return (NULL);
	result = malloc(total_mem);
	if (!result)
		return (NULL);
	ft_bzero(result, total_mem);
	return (result);
}

void	draw_vertical_line(int x, int start, int end, int color)
{
	while (start < end)
	{
		mlx_pixel_put(d()->mlx, d()->win_ptr, start, x, color);
		start += 2;
	}
}

void	max_map(void)
{
	int	y;

	y = 0;
	while (y < d()->map_h - 1)
	{
		if (d()->max_x < ft_strlen(d()->map[y]))
			d()->max_x = ft_strlen(d()->map[y]);
		y++;
	}
}

void	get_index(void)
{
	if (d()->side == 0)
	{
		if (d()->ray_dir_x < 0)
			d()->texture_index = 3;
		else
			d()->texture_index = 2;
	}
	else
	{
		if (d()->ray_dir_y > 0)
			d()->texture_index = 1;
		else
			d()->texture_index = 0;
	}
}
