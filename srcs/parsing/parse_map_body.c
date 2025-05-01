/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_body.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:59:42 by gcatarin          #+#    #+#             */
/*   Updated: 2025/05/01 22:41:29 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cubed.h"

static void	check_char(char c, int x, int y)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'W' \
&& c != 'E' && c != '.')
		error("Error\nWrong character found in map!");
	if (c == 'N')
		d()->player_a = 3 * PI / 2;
	else if (c == 'S')
		d()->player_a = PI / 2;
	else if (c == 'W')
		d()->player_a = PI;
	else if (c == 'E')
		d()->player_a = 0;
	d()->plane_x = -sin(d()->player_a) * 0.66;
	d()->plane_y = -cos(d()->player_a) * 0.66;
	d()->player_dx = cos(d()->player_a) * d()->p_speed;
	d()->player_dy = sin(d()->player_a) * d()->p_speed;
	if (++d()->n_player > 1)
		error("Error\nWrong player count!");
	d()->player_x = (x * 64) + 32;
	d()->player_y = (y * 64) + 32; // texture size
}

void	load_map_body(void)
{
	int	x;
	int	y;

	y = 0;
	while (d()->map[y])
	{
		x = 0;
		while (d()->map[y][x])
		{
			if (d()->map[y][x] != '1' && \
d()->map[y][x] != '0' && d()->map[y][x] != '.')
				check_char(d()->map[y][x], x, y);
			x++;
		}
		y++;
	}
	d()->map_w = ft_strlen(d()->map[y - 1]);
}

void	map_flood_fill(int x, int y, char **map, int size)
{
	char	c;

	c = map[y][x];
	if (y < 0 || y >= size || x < 0 || c == '1' || c == '-')
		return ;
	if (ft_strlen(map[y]) <= x)
		return ;
	if (c == '.')
		error("Error\nFound a leak in the map structure!");
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '0')
		map[y][x] = '-';
	map_flood_fill(x + 1, y, map, size);
	map_flood_fill(x - 1, y, map, size);
	map_flood_fill(x, y + 1, map, size);
	map_flood_fill(x, y - 1, map, size);
}
