/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnuncio- <jnuncio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:45:43 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/10 20:08:19 by jnuncio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	error(char *s)
{
	ft_putendl_fd(s, 2);
	free_double_char(d()->map);
	free_double_char(d()->textures);
	free_double_int(d()->pixels);
	free(d()->map_ea);
	free(d()->map_so);
	free(d()->map_no);
	free(d()->map_we);
	mlx_destroy_window(d()->mlx, d()->win_ptr);
	mlx_destroy_display(d()->mlx);
	free(d()->mlx);
	exit(1);
}

int	destroy_hook(void)
{
	error("\nexit");
	return (1);
}

int	free_double_char(char **map)
{
	int	i;

	i = -1;
	if (!map)
		return (1);
	while (map[++i])
		free(map[i]);
	free(map);
	return (1);
}

int	free_double_int(int **map)
{
	int	i;

	i = -1;
	if (!map)
		return (1);
	while (map[++i])
		free(map[i]);
	free(map);
	return (1);
}
