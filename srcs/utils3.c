/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:40:23 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/13 12:35:30 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static size_t	ft_strlcpy_map(char *dest, const char *src, size_t size)
{
	size_t	count;

	count = 0;
	if (size == 0)
		return (ft_strlen(src));
	dest[0] = '.';
	while (src[count] != '\0')
	{
		if (ft_isspace(src[count]) == 1)
			dest[count + 1] = '.';
		else
			dest[count + 1] = src[count];
		count++;
	}
	while (count < (size - 1))
	{
		dest[count + 1] = '.';
		count++;
	}
	dest[count] = '\0';
	return (ft_strlen(src));
}

void	init_map(int width, int j)
{
	int		i;
	void	*tmp;
	void	*tmp1;

	i = 1;
	tmp = ft_calloc(sizeof(char *), d()->map_h + 3);
	d()->map = tmp;
	if (!d()->map)
		error("Error\n Couldn't allocate map\n");
	(d())->map[0] = ft_calloc(width + 3, sizeof(char));
	ft_memset(d()->map[0], width + 2, '.');
	while (i <= d()->map_h)
	{
		tmp1 = ft_calloc(width + 3, sizeof(char));
		d()->map[i] = tmp1;
		if (!d()->map[i])
			error("Error\n Couldn't allocate map line\n");
		ft_strlcpy_map(d()->map[i], d()->full_map[j], width + 3);
		j++;
		i++;
	}
	(d())->map[i] = ft_calloc(width + 3, sizeof(char));
	ft_memset(d()->map[i], width + 2, '.');
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
