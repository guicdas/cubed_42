/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:44:00 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/11 22:29:48 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static int	get_color(char *s)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (s[i])
	{
		ret *= 10;
		ret += (s[i] - 48);
		i++;
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

static int	color_args(char *str)
{
	char	**args;
	size_t	size;
	int		*rgb_tab;
	int		ret;

	rgb_tab = calloc(3, sizeof(int));
	args = ft_split(str, ' ');
	size = ft_strlen_array(args);
	if (size != 2)
	{
		error("Error\n");
		return (free_double((void **)args), NULL);
	}
	str = args[1];
	args[1] = ft_split(args[1], ',');
	size = ft_strlen_array(args[1]);
	if (size != 3)
	{
		error("Error\n");
		return (free_double((void **)args[1]), NULL);
	}
	rgb_tab[0] = get_color(args[1]);
	rgb_tab[1] = get_color(args[1]);
	rgb_tab[2] = get_color(args[1]);
	ret = convert_rgb_to_hex(rgb_tab);
	return (free_double((void **)args), ret);
}

void	limits_colors(char *s)
{
	if (s[0] == 'F' && ft_isspace(s[2]))
	{
		if (d()->map_f)
			error("Error\nMultiple floor colors in map file.\n");
		d()->map_f = color_args(s);
	}
	else if (s[0] == 'C' && ft_isspace(s[2]))
	{
		if (d()->map_c)
			error("Error\nMultiple ceiling colors in map file.\n");
		d()->map_c = color_args(s);
	}
}
