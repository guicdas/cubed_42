/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 01:38:42 by gcatarin          #+#    #+#             */
/*   Updated: 2025/05/01 17:00:25 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cubed.h"

static char	*get_info(char *str)
{
	char	**args;
	size_t	size;

	args = ft_split(str, SPACE);
	size = ft_strlen_array(args);
	if (size != 2)
		return (free_double((void **)args), NULL);
	str = args[1];
	args[1] = NULL;
	return (free_double((void **)args), str);
}

static int	verify_header_line(char *texture, char *s, char **info)
{
	int	len;

	len = ft_strlen(texture);
	if (ft_strncmp(s, texture, len) == 0 && ft_isspace(s[len]))
	{
		if (*info)
			error("Error\nRepeated information in map header.");
		if (len == 1)
			*info = s;
		else
			*info = get_info(s);
		d()->n_info++;
		return (1);
	}
	return (0);
}

int	verify_map_header(char *s)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (verify_header_line(d()->file_header[i].key, \
s, d()->file_header[i].target) == 1)
			return (1);
		i++;
	}
	error("Error\nWrong textures for .cub file");
	return (0);
}

void	init_texture(t_img *img)
{
	img->image = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->endian = 0;
	img->linesize = 0;
}
