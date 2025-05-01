/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 01:39:00 by gcatarin          #+#    #+#             */
/*   Updated: 2025/05/01 03:41:49 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cubed.h"

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
