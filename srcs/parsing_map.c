/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnuncio- <jnuncio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:12:37 by mneves-l          #+#    #+#             */
/*   Updated: 2024/06/13 10:59:59 by jnuncio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static void	init_orientation(float a, float px, float py)
{
	d()->player_a = a;
	d()->plane_x = px;
	d()->plane_y = py;
}

int	check_char(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'W' \
	&& c != 'E' && c != '\2')
		return (1);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (c == 'N')
			init_orientation(3 * PI / 2 + 0, 0.66, 0);
		else if (c == 'S')
			init_orientation(PI / 2 + 0, -0.66, 0);
		else if (c == 'W')
			init_orientation(PI + 0, 0, -0.66);
		else if (c == 'E')
			init_orientation(0, 0, 0.66);
		return (2);
	}
	else
		return (0);
}

void	map_check_matriz(void)
{
	int	x;
	int	y;

	y = 0;
	while (d()->map[y])
	{
		x = 0;
		while (d()->map[y][x])
		{
			if (check_char(d()->map[y][x]) == 1)
				error("Error\nWrong character found in map!\n");
			if (check_char(d()->map[y][x]) == 2)
			{
				d()->player_x = (x * 64) + 32;
				d()->player_y = (y * 64) + 32;
				d()->player_dx = cos(d()->player_a) * d()->player_speed;
				d()->player_dy = sin(d()->player_a) * d()->player_speed;
				d()->n_player++;
			}
			x++;
		}
		y++;
	}
	d()->map_w = ft_strlen(d()->map[y - 1]);
}

void	map_flood_fill(int x, int y, char **map, int size)
{
	if (y < 0 || y >= size || x < 0 || map[y][x] == '1' \
	|| map[y][x] == '-')
		return ;
	if (ft_strlen(map[y]) <= x)
		return ;
	if (map[y][x] == '\2')
		error("Error\nFound a leak in the map structure!");
	if (check_char(map[y][x]) == 2)
		map[y][x] = '-';
	if (map[y][x] == '0')
		map[y][x] = '-';
	map_flood_fill(x + 1, y, map, size); 
	map_flood_fill(x - 1, y, map, size);
	map_flood_fill(x, y + 1, map, size);
	map_flood_fill(x, y - 1, map, size);
}
