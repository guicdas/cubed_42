/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnuncio- <jnuncio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:50:59 by mneves-l          #+#    #+#             */
/*   Updated: 2024/06/12 21:17:07 by jnuncio-         ###   ########.fr       */
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

static char	**__split(char const *s, char c, int j, char **list)
{
	char	*t;
	int		i;

	i = 0;
	t = 0;
	while (s && *s == c && *s)
		s++;
	while (s && s[i] != c && s[i])
		i++;
	if (i > 0)
		t = ft_calloc((i + 1), sizeof(char));
	i = 0;
	while (s && t && *s != c && *s)
		t[i++] = *s++;
	if (++j >= 0 && i)
		list = __split(s, c, j, list);
	else if (!list)
		list = ft_calloc(j, sizeof(char *));
	if (list)
		list[--j] = t;
	return (list);
}

char	**ft_split(char const *s, char c)
{
	return (__split((char *) s, c, 0, NULL));
}

int	check_c(const char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
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
