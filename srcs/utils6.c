/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnuncio- <jnuncio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:17:36 by jnuncio-          #+#    #+#             */
/*   Updated: 2024/06/12 21:19:27 by jnuncio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static char	*tes(char *str)
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
		d()->map_ea = tes(s);
		d()->n_info++;
	}
	else if (s[0] == 'W' && s[1] == 'E' && ft_isspace(s[2]))
	{
		if (d()->map_we)
			error("Error\nMultiple WE textures in map file.\n");
		d()->map_we = tes(s);
		d()->n_info++;
	}
}

void	clean_info(char *s)
{
	if (s[0] == 'N' && s[1] == 'O' && ft_isspace(s[2]))
	{
		if (d()->map_no)
			error("Error\nMultiple NO textures in map file.\n");
		d()->map_no = tes(s);
		d()->n_info++;
	}
	else if (s[0] == 'S' && s[1] == 'O' && ft_isspace(s[2]))
	{
		if (d()->map_so)
			error("Error\nMultiple SO textures in map file.\n");
		d()->map_so = tes(s);
		d()->n_info++;
	}
	else
		clean_infos(s);
}
