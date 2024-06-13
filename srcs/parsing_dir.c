/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnuncio- <jnuncio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:46:55 by mneves-l          #+#    #+#             */
/*   Updated: 2024/06/13 11:12:27 by jnuncio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

static void	get_map_lines(int fd)
{
	char	*tmp;
	char	**temp;
	int		n_lines;

	n_lines = 0;
	while (1)
	{
		tmp = get_next_line(fd);
		if (tmp == NULL)
			break ;
		n_lines++;
		free(tmp);
	}
	temp = ft_calloc(sizeof(char *), n_lines + 1);
	d()->full_map = temp;
	if (!d()->full_map)
		error("Error\n Couldn't allocate full map\n");
}

static int	copy_map(int fd2)
{
	char	*tmp;
	char	*temp;
	int		n_lines;

	n_lines = 0;
	while (1)
	{
		tmp = get_next_line(fd2);
		if (tmp == NULL)
			break ;
		if (tmp[0] != '\n')
			temp = clean_string(tmp, 0, 0);
		else
		{
			temp = ft_calloc(sizeof(char), 2);
			temp[0] = '\n';
			temp[1] = '\0';
		}
		d()->full_map[n_lines] = temp;
		n_lines++;
		free(tmp);
	}
	d()->full_map[n_lines] = NULL;
	return (n_lines);
}

static void	load_map(int nlines)
{
	int	i;
	int	j;
	int	max_width;

	i = -1;
	j = 0;
	max_width = 0;
	while (d()->full_map[++i])
	{
		if (check_for_element(d()->full_map[i]) == 2)
		{
			d()->map_h++;
			if (max_width < ft_strlen(d()->full_map[i]))
				max_width = ft_strlen(d()->full_map[i]);
		}
	}
	if (d()->n_info != 6)
		error("Error\nMissing element in .cub file!");
	if (!d()->map_h)
		error("Error\nMissing map in .cub file!\n");
	init_map(max_width, nlines - d()->map_h);
}

int	check_for_element(char *s)
{
	while (s && ft_isspace(*s) == 1)
		s++;
	if (d()->n_info == 6)
	{
		(d())->init_map_flag += (s && *s != '\0');
		return (1 + (d()->init_map_flag > 0));
	}
	if (s && *s)
	{
		clean_info(s);
		limits_colors(s);
		return (1);
	}
	return (0);
}

void	parsing(char **av)
{
	int	fd;
	int	fd2;
	int	i;

	fd = open(av[1], O_RDONLY, 0700);
	if (fd < 0)
		error("Error\nCouldn't open map\n");
	fd2 = open(av[1], O_RDONLY, 0700);
	if (fd2 < 0)
	{
		close(fd);
		error("Error\nCouldn't open map\n");
	}
	get_map_lines(fd);
	close(fd);
	i = copy_map(fd2);
	close(fd2);
	load_map(i);
	map_check_matriz();
	if (d()->n_player != 1)
		error("Error\nWrong player count!\n");
	map_flood_fill((int)d()->player_x / 64, (int)d()->player_y / 64, \
	d()->map, d()->map_h);
}
