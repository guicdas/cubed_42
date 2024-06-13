/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnuncio- <jnuncio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:45:43 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/13 11:11:51 by jnuncio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static void	free_maps(void)
{
	int	i;

	i = 0;
	while (d()->map && d()->map[i])
		free(d()->map[i++]);
	free(d()->map);
	i = 0;
	while (d()->full_map && d()->full_map[i])
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

void	free_double(void **map)
{
	int	i;

	i = -1;
	if (!map)
		return ;
	while (map[++i])
		free(map[i]);
	free(map);
}

void	free_image(void)
{
	if (d()->wall.image)
		mlx_destroy_image(d()->mlx, d()->wall.image);
	if (d()->exit.image)
		mlx_destroy_image(d()->mlx, d()->exit.image);
	if (d()->floor.image)
		mlx_destroy_image(d()->mlx, d()->floor.image);
}

void	error(char *s)
{
	ft_putendl_fd(s, 2);
	free_maps();
	if (d()->textures)
		free_double((void **)d()->textures);
	if (d()->pixels)
		free_double((void **)d()->pixels);
	free_info();
	if (d()->mlx)
		free_image();
	if (d()->mlx && d()->win_ptr)
		mlx_destroy_window(d()->mlx, d()->win_ptr);
	if (d()->mlx)
		mlx_destroy_display(d()->mlx);
	free(d()->mlx);
	exit(0);
}
