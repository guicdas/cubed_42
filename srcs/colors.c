/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:44:00 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/10 19:26:07 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static int	get_color(char *s, int *i)
{
	int	ret;

	ret = 0;
	if (!s)
	{
		printf("Error\nWrong input for rgb colors\n");
		exit(1);
	}
	while (s[*i] && s[*i] != ',')
	{
		ret *= 10;
		ret += (s[*i] - 48);
		(*i)++;
	}
	while (s[*i] && ft_isdigit(s[*i]) == 0)
	{
		if (ft_isspace(s[*i]) != 1 && s[*i] != ',')
		{
			printf("Error\nWrong character in rgb colors!\n");
			exit(1);
		}
		(*i)++;
	}
	return (ret);
}

static unsigned long	convert_rgb_to_hex(int *rgb_tab)
{
	unsigned long	result;
	int				r;
	int				g;
	int				b;

	r = rgb_tab[0];
	g = rgb_tab[1];
	b = rgb_tab[2];
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
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
