/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_body.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:59:42 by gcatarin          #+#    #+#             */
/*   Updated: 2025/05/02 00:51:23 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cubed.h"

static void	check_player_position(char c, int x, int y)
{
	static int	player_count = 0;

	if (c != 'N' && c != 'S' && c != 'W' && c != 'E' && c != 'D')
		error("Error\nWrong character found in map!");
	if (++player_count > 1) // verifica isto
		error("Error\nWrong player count!");
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
	d()->player_x = (x * 64) + 32;
	d()->player_y = (y * 64) + 32; // texture size
	d()->player_x_map = x;
	d()->player_y_map = y;
}

void	load_map_body(void)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (d()->map[y])
	{
		x = 0;
		while (d()->map[y][x])
		{
			c = d()->map[y][x];
			if (c != '1' && c != 'D' && c != '0' && c != '.')
				check_player_position(d()->map[y][x], x, y);
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
	if (y < 0 || y >= size || x < 0 || c == '1' || c == 'D' || c == '-')
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
