/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:44:00 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/08 20:06:03 by gcatarin         ###   ########.fr       */
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
/*	erros possiveis
		single digits (0, 1..) 
		+ tirar atoi e meter ft_atoi
		+ se a linha F ou C tiver mal escrita
	*/

int	limits_colors(char *s)
{
	char	*tmp;
	int		i;
	int		ret;

	i = 0;
	tmp = clean_string(s, 1, 1);
	ret = create_trgb(0, get_color(tmp, &i), \
	get_color(tmp, &i), get_color(tmp, &i));
	free(tmp);
	
	return (ret);
}
