/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnuncio- <jnuncio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:44:00 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/10 21:00:25 by jnuncio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static int	get_color(char *s, int *i)
{
	int	ret;

	ret = 0;
	while (s[*i] && s[*i] != ',')
	{
		ret *= 10;
		ret += (s[*i] - 48);
		(*i)++;
	}
	(*i)++;
	return (ret);
}

static int	create_trgb(int t, int r, int g, int b)
{
	return (put_b_nbr(t << 24, HEXA, 16) + put_b_nbr(r << 16, HEXA, 16) + \
	put_b_nbr(g << 8, HEXA, 16) + put_b_nbr(b, HEXA, 16));
}

int	limits_colors(char *s)
{
	char			*tmp;
	int				i;
	unsigned long	ret;
	int				*rgb_tab;

	rgb_tab = calloc(3, sizeof(int));
	i = 0;
	tmp = clean_string(s, 1, 1);
	rgb_tab[0] = get_color(tmp, &i);
	rgb_tab[1] = get_color(tmp, &i);
	rgb_tab[2] = get_color(tmp, &i);
	ret = convert_rgb_to_hex(rgb_tab);
	free(rgb_tab);
	free(tmp);
	return (ret);
}
