/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:45:43 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/08 19:47:48 by gcatarin         ###   ########.fr       */
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

int	destroy_hook()
{
	error("\nexit");
	return (1);
}
