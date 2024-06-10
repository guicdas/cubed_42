/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnuncio- <jnuncio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:01:48 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/09 14:43:50 by jnuncio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	movekey_hook(int keypress)
{
	init_values();
	move(keypress);
	raycaster();
	render_frame();
	print_minimap();
	mlx_string_put(d()->mlx, d()->win_ptr, 2, 12, \
	RED, ft_itoa(d()->frames++, 10, DECA));
	return (0);
}
