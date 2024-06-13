/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnuncio- <jnuncio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:50:59 by mneves-l          #+#    #+#             */
/*   Updated: 2024/06/13 11:53:20 by jnuncio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static char	*get_info(char *str)
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

static void	clean_infos(char *s)
{
	if (s[0] == 'E' && s[1] == 'A' && ft_isspace(s[2]))
	{
		if (d()->map_ea)
			error("Error\nMultiple EA textures in map file.\n");
		d()->map_ea = get_info(s);
		d()->n_info++;
	}
	else if (s[0] == 'W' && s[1] == 'E' && ft_isspace(s[2]))
	{
		if (d()->map_we)
			error("Error\nMultiple WE textures in map file.\n");
		d()->map_we = get_info(s);
		d()->n_info++;
	}
}

void	clean_info(char *s)
{
	if (s[0] == 'N' && s[1] == 'O' && ft_isspace(s[2]))
	{
		if (d()->map_no)
			error("Error\nMultiple NO textures in map file.\n");
		d()->map_no = get_info(s);
		d()->n_info++;
	}
	else if (s[0] == 'S' && s[1] == 'O' && ft_isspace(s[2]))
	{
		if (d()->map_so)
			error("Error\nMultiple SO textures in map file.\n");
		d()->map_so = get_info(s);
		d()->n_info++;
	}
	else
		clean_infos(s);
}

void	init_texture(t_img *img)
{
	img->image = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->endian = 0;
	img->linesize = 0;
}
