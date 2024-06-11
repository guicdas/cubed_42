/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:50:59 by mneves-l          #+#    #+#             */
/*   Updated: 2024/06/11 21:34:34 by gcatarin         ###   ########.fr       */
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