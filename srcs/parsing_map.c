/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:12:37 by mneves-l          #+#    #+#             */
/*   Updated: 2024/06/09 20:15:59 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	check_char(char c)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'W' \
	&& c != 'E' && c != ' ' && c != '\n')
		return (1);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (c == 'N')
			d()->player_a = 3 * PI / 2;
		else if (c == 'S')
			d()->player_a = PI / 2;
		else if (c == 'W')
			d()->player_a = PI;
		else if (c == 'E')
			d()->player_a = 0;
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
				d()->player_x = x * 64;
				d()->player_y = y * 64;
				d()->player_dx = cos(d()->player_a);
				d()->player_dy = sin(d()->player_a);
			}
			x++;
		}
		y++;
	}
	d()->map_w = ft_strlen(d()->map[y - 1]);
}

//check if the map is surrounded and if have Player exit proportions
void	map_flood_fill(int x, int y, char **map, int size)
{
	if (y < 0 || y >= size || x < 0 || map[y][x] == '1' \
	|| map[y][x] == '-' || map[y][x] == 'P')
		return ;
	if (ft_strlen(map[y]) <= x)
		return ;
	if (map[y][x] == ' ')
	{
		printf("Flood_fill found a leak in the map[%d][%d]\n", y, x);
		return ;
	}
	if (check_char(map[y][x]) == 2)
	{
		printf("Flood_fill found a Player[%d][%d]\n", y, x);
		map[y][x] = 'P';
	}
	if (map[y][x] == '0')
		map[y][x] = '-';
	map_flood_fill(x + 1, y, map, size); 
	map_flood_fill(x - 1, y, map, size);
	map_flood_fill(x, y + 1, map, size);
	map_flood_fill(x, y - 1, map, size);
}
