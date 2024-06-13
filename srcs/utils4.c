/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:50:59 by mneves-l          #+#    #+#             */
/*   Updated: 2024/06/13 14:08:13 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

int	ft_strlen_array(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

static int	is_char(char c, char *str)
{
	while (str && *str)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

static char	**split_ft(char const *s, char *c, int j, char **list)
{
	char	*t;
	int		i;

	i = 0;
	t = 0;
	while (s && is_char(*s, c) && *s)
		s++;
	while (s && is_char(s[i], c) == 0 && s[i])
		i++;
	if (i > 0)
		t = ft_calloc((i + 1), sizeof(char));
	i = 0;
	while (s && t && is_char(*s, c) == 0 && *s)
		t[i++] = *s++;
	if (++j >= 0 && i)
		list = split_ft(s, c, j, list);
	else if (!list)
		list = ft_calloc(j, sizeof(char *));
	if (list)
		list[--j] = t;
	return (list);
}

char	**ft_split(char const *s, char *c)
{
	return (split_ft((char *) s, c, 0, NULL));
}

void	get_index(void)
{
	if (d()->side == 0)
	{
		if (d()->ray_dir_x < 0)
			d()->texture_index = 3;
		else
			d()->texture_index = 2;
	}
	else
	{
		if (d()->ray_dir_y > 0)
			d()->texture_index = 1;
		else
			d()->texture_index = 0;
	}
}
