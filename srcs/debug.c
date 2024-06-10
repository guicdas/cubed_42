/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:25:08 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/10 19:12:42 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	info_print(void)
{
	printf("------------ PARSING MAP_TOKENS -----------\n");
	printf("Value NO -> |%s|\n", (d()->map_no));
	printf("Value SO -> |%s|\n", (d()->map_so));
	printf("Value WE -> |%s|\n", (d()->map_we));
	printf("Value EA -> |%s|\n", (d()->map_ea));
	printf("Value F  -> |%d|\n", (d()->map_f));
	printf("Value C  -> |%d|\n\n", (d()->map_c));
	printf("player_pos [x][y]= [%f][%f]\n", d()->player_x, d()->player_y);
}

void	map_print(void)
{
	int	i;
	int	j;

	i = 0;
	while (d()->map[i])
	{
		j = 0;
		while (j < d()->map_w)
			printf("[%d%d] - ", j++, i);
		printf("\n");
		i++;
	}
}

void	debug_dda(void)
{
	printf("map HEIGHT: %d\n", d()->map_h);
	printf("map WIDTHy: %d\n", d()->map_w);
	printf("cam: %f\n", d()->camera_x);
	printf("ray x: %f\n", d()->ray_dir_x);
	printf("ray y: %f\n", d()->ray_dir_y);
	printf("map x: %d\n", d()->map_x);
	printf("map y: %d\n", d()->map_y);
	printf("ddist x: %f\n", d()->delta_dist_x);
	printf("ddist y: %f\n", d()->delta_dist_y);
	printf("sX: %d, sY; %d\n", d()->step_x, d()->step_y);
	printf("sideX: %f, sideY: %f\n", d()->side_dist_x, d()->side_dist_y);
}
