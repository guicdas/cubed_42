/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:40:23 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/10 22:20:51 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	init_pixels(void)
{
	int		i;
	void	*tmp;
	void	*tmp1;

	i = 0;
	if (d()->pixels)
		free_double_int(d()->pixels);
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

void	init_map(int width)
{
	int		i;
	void	*tmp;
	void	*tmp1;
	(void)tmp1;
	(void)width;
	i = 0;

	tmp = ft_calloc(sizeof(char *), d()->map_h + 1);
	d()->map = tmp;
	if (!d()->map)
		error("Error\n Couldn't allocate map\n");
	while (i < d()->map_h - 1)
	{
		tmp1 = ft_calloc(width + 1, sizeof(char));
		d()->map[i] = tmp1;
		if (!d()->map[i])
			error("Error\n Couldn't allocate map line\n");
		i++;
	}
}

void	clean_info(char c, char *str)
{
	char	*tmp;
	int	i;

	i = 2;
	tmp = clean_string(str, 2, 1);
	if (c == 'N')
		d()->map_no = tmp;
	if (c == 'S')
		d()->map_so = tmp;
	if (c == 'E')
		d()->map_ea = tmp;
	if (c == 'W')
		d()->map_we = tmp;
}