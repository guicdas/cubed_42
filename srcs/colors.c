/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:44:00 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/13 13:44:50 by gcatarin         ###   ########.fr       */
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
		if (s[i] < '0' || s[i] > '9')
			error("Error\nInvalid character in rgb format");
		ret *= 10;
		ret += (s[i] - 48);
		i++;
	}
	return (ret);
}

static unsigned long	convert_rgb_to_hex(char **args)
{
	unsigned long	result;
	int				r;
	int				g;
	int				b;

	result = 0;
	r = get_color(args[0]);
	g = get_color(args[1]);
	b = get_color(args[2]);
	if (r > 255 || g > 255 || b > 255)
		error("Error\nInvalid RGB range.\n");
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}

static int	rgb_args(char *s)
{
	char	**args;
	int		ret;
	int		size;

	args = ft_split(s, ",");
	size = ft_strlen_array(args);
	if (size != 3)
	{
		free_double((void **)args);
		error("Error\nInvalid RGB format.\n");
	}
	ret = convert_rgb_to_hex(args);
	free_double((void **)args);
	return (ret);
}

static int	color_args(char *str)
{
	char	**args;
	size_t	size;
	int		ret;

	ret = 0;
	args = ft_split(str, SPACE);
	size = ft_strlen_array(args);
	if (size != 2)
	{
		free_double((void **)args);
		error("Error\nInvalid RGB format.\n");
	}
	ret = rgb_args(args[1]);
	free_double((void **)args);
	return (ret);
}

int	limits_colors(char *s)
{
	if (s[0] == 'F' && ft_isspace(s[1]))
	{
		if (d()->map_f)
			error("Error\nMultiple floor colors in map file.\n");
		d()->map_f = color_args(s);
		d()->n_info++;
		return (1);
	}
	else if (s[0] == 'C' && ft_isspace(s[1]))
	{
		if (d()->map_c)
			error("Error\nMultiple ceiling colors in map file.\n");
		d()->map_c = color_args(s);
		d()->n_info++;
		return (1);
	}
	return (0);
}
