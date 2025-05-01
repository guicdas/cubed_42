/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:44:00 by gcatarin          #+#    #+#             */
/*   Updated: 2025/05/01 03:23:35 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cubed.h"

static int	get_single_color(char *s)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		ret = ret * 10 + (s[i] - '0');
		i++;
	}
	return (ret);
}

static int	verify_rgb_value(char **args, int index)
{
	int	rgb_value;

	if (ft_strlen(args[index]) <= 3)
	{
		rgb_value = get_single_color(args[index]);
		if (rgb_value > 0 && rgb_value < 256)
			return (rgb_value);
	}
	free_double((void **)args);
	return (error("Error\nInvalid RGB input."), NULL);
}

static unsigned long	calculate_rgb_value(char **s)
{
	int					rgb_value;
	char				**args;
	unsigned long		ret;

	args = ft_split(s[1], COMMA);
	if (ft_strlen_array(args) == 3)
	{
		rgb_value = verify_rgb_value(args, 0);
		ret = ((rgb_value & 0xff) << 16);
		rgb_value = verify_rgb_value(args, 1);
		ret += ((rgb_value & 0xff) << 8);
		rgb_value = verify_rgb_value(args, 2);
		free_double((char **)args);
		return (ret + rgb_value & 0xff);
	}
	free_double((void **)args);
	return (error("Error\nInvalid RGB format.\n"), NULL);
}

int	get_color_rgb(char *str)
{
	char	**args;
	int		ret;

	args = ft_split(str, SPACE);
	if (ft_strlen_array(args) == 2)
	{
		ret = calculate_rgb_value(args);
		return (free_double((void **)args), ret);
	}
	free_double((void **)args);
	return (error("Error\nInvalid RGB format."), NULL);
}
