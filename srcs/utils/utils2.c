/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:40:23 by gcatarin          #+#    #+#             */
/*   Updated: 2025/05/01 01:38:36 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cubed.h"

static size_t	ft_strlcpy_map(char *dest, const char *src, size_t size)
{
	size_t	count;

	count = 0;
	if (size == 0)
		return (ft_strlen(src));
	dest[0] = '.';
	while (src[count] != '\0')
	{
		if (ft_isspace(src[count]) == 1)
			dest[count + 1] = '.';
		else
			dest[count + 1] = src[count];
		count++;
	}
	while (count < (size - 1))
	{
		dest[count + 1] = '.';
		count++;
	}
	dest[count] = '\0';
	return (ft_strlen(src));
}

static void	ft_memset(void *s, size_t n, char c)
{
	size_t	i;

	i = 0;
	if (n < 1)
		return ;
	while (n-- >= 1)
		((char *)s)[i++] = c;
}

void	init_map(int width, int j)
{
	int		i;
	void	*tmp;
	void	*tmp1;

	i = 1;
	tmp = ft_calloc(sizeof(char *), d()->map_h + 3);
	d()->map = tmp;
	if (!d()->map)
		error("Error\n Couldn't allocate map\n");
	(d())->map[0] = ft_calloc(width + 3, sizeof(char));
	ft_memset(d()->map[0], width + 2, '.');
	while (i <= d()->map_h)
	{
		tmp1 = ft_calloc(width + 3, sizeof(char));
		d()->map[i] = tmp1;
		if (!d()->map[i])
			error("Error\n Couldn't allocate map line\n");
		ft_strlcpy_map(d()->map[i], d()->full_map[j], width + 3);
		j++;
		i++;
	}
	(d())->map[i] = ft_calloc(width + 3, sizeof(char));
	ft_memset(d()->map[i], width + 2, '.');
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
