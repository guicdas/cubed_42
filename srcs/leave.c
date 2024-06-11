/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:45:43 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/11 17:18:00 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static void	free_maps(void)
{
	int	i;

	i = 0;
	while (i < d()->map_h)
		free(d()->map[i++]);
	free(d()->map);
	i = 0;
	while (d()->full_map[i])
		free(d()->full_map[i++]);
	free(d()->full_map);
}

static void	free_info(void)
{
	if (d()->map_ea)
		free(d()->map_ea);
	if (d()->map_so)
		free(d()->map_so);
	if (d()->map_no)
		free(d()->map_no);
	if (d()->map_we)
		free(d()->map_we);
}

void	error(char *s)
{
	ft_putendl_fd(s, 2);
	free_maps();
	if (d()->textures)
		free_double_int(d()->textures);
	if (d()->pixels)
		free_double_int(d()->pixels);
	free_info();
	if (d()->mlx && d()->win_ptr)
		mlx_destroy_window(d()->mlx, d()->win_ptr);
	if (d()->mlx)
		mlx_destroy_display(d()->mlx);
	free(d()->mlx);
	exit(0);
}

int	destroy_hook(void)
{
	error("\nexit");
	return (0);
}
