/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:40:23 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/11 22:31:30 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	count;

	count = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[count] != '\0')
	{
		if (ft_isspace(src[count]) == 1)
			dest[count] = '\2';
		else
			dest[count] = src[count];
		count++;
	}
	while (count < (size - 1))
	{
		dest[count] = '\2';
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

	i = 0;
	tmp = ft_calloc(sizeof(char *), d()->map_h + 1);
	d()->map = tmp;
	if (!d()->map)
		error("Error\n Couldn't allocate map\n");
	while (i < d()->map_h)
	{
		tmp1 = ft_calloc(width + 2, sizeof(char));
		d()->map[i] = tmp1;
		if (!d()->map[i])
			error("Error\n Couldn't allocate map line\n");
		ft_strlcpy(d()->map[i], d()->full_map[j], width + 2);
		j++;
		i++;
	}
}

char *tes(char *str)
{
	char	**args;
	size_t	size;

	args = ft_split(str, ' ');
	size = ft_strlen_array(args);
	if (size != 2)
		return (free_double((void **)args), NULL);
	str = args[1];
	args[1] = NULL;
	return (free_double((void **)args), str);
}

void	clean_info(char *s)
{
	if (s[0] == 'N' && s[1] == 'O' && ft_isspace(s[2]))
	{
		if (d()->map_no)
			error("Error\nMultiple NO textures in map file.\n");
		d()->map_no = tes(s);
	}
	if (s[0] == 'S' && s[1] == 'O' && ft_isspace(s[2]))
	{
		if (d()->map_so)
			error("Error\nMultiple SO textures in map file.\n");	
		d()->map_so = tes(s);
	}
	if (s[0] == 'E' && s[1] == 'A' && ft_isspace(s[2]))
	{	
		if (d()->map_ea)
			error("Error\nMultiple EA textures in map file.\n");
		d()->map_ea = tes(s);
	}
	if (s[0] == 'W' && s[1] == 'E' && ft_isspace(s[2]))
	{	
		if (d()->map_we)
			error("Error\nMultiple WE textures in map file.\n");
		d()->map_we = tes(s);
	}
}
