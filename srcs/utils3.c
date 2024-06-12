/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnuncio- <jnuncio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:40:23 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/12 21:19:19 by jnuncio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	count;

	count = 0;
	if (size == 0)
		return (ft_strlen(src));
	dest[0] = '9';
	while (src[count] != '\0')
	{
		if (ft_isspace(src[count]) == 1)
			dest[count + 1] = '9';
		else
			dest[count + 1] = src[count];
		count++;
	}
	while (count < (size - 1))
	{
		dest[count + 1] = '9';
		count++;
	}
	dest[count] = '\0';
	return (ft_strlen(src));
}

void	init_pixels(void)
{
	int		i;
	void	*tmp;
	void	*tmp1;

	i = 0;
	if (d()->pixels)
		free_double((void **)d()->pixels);
	tmp = ft_calloc(d()->screen_height + 1, sizeof(int *));
	d()->pixels = tmp;
	if (!d()->pixels)
		error("Error\n Couldn't allocate pixels\n");
	while (i < d()->screen_height)
	{
		tmp1 = ft_calloc(d()->screen_width + 1, sizeof(int));
		d()->pixels[i] = tmp1;
		if (!d()->pixels[i])
			error("Error\n Couldn't allocate pixels\n");
		i++;
	}
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
	ft_memset(d()->map[0], width + 2, '9');
	while (i <= d()->map_h)
	{
		tmp1 = ft_calloc(width + 3, sizeof(char));
		d()->map[i] = tmp1;
		if (!d()->map[i])
			error("Error\n Couldn't allocate map line\n");
		ft_strlcpy(d()->map[i], d()->full_map[j], width + 3);
		j++;
		i++;
	}
	(d())->map[i] = ft_calloc(width + 3, sizeof(char));
	ft_memset(d()->map[i], width + 2, '9');
}
