/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:38:24 by gcatarin          #+#    #+#             */
/*   Updated: 2025/05/01 21:54:11 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cubed.h"

static void	allocate_maplines(int fd)
{
	char	*tmp;
	int		n_lines;

	n_lines = 1;
	while (n_lines++)
	{
		tmp = get_next_line(fd);
		if (tmp == NULL)
			break ;
		free(tmp);
	}
	if (n_lines - 2 <= 0)
		error("Error\nEmpty .cub file");
	d()->full_map = ft_calloc(sizeof(char *), n_lines - 1);
	if (!d()->full_map)
		error("Error\nCouldn't allocate full map");
	//temp ?
}

static int	copy_full_map_file(int fd)
{
	char	*tmp;
	char	*temp;
	int		n_lines;

	n_lines = 0;
	while (1)
	{
		tmp = get_next_line(fd);
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
		d()->full_map[n_lines++] = temp;
		//temp = NULL ou assim
		free(tmp);
	}
	d()->full_map[n_lines] = NULL;
	return (n_lines);
}

static int	check_for_element(char *s)
{
	while (s && ft_isspace(*s) == 1)
		s++;
	if (d()->n_info == 6)
	{
		(d())->init_map_flag += (s && *s != '\0');
		return (1 + (d()->init_map_flag > 0));
	}
	if (s && *s)
		return (verify_map_header(s));
	return (0);
}

static void	load_map_header(int nlines)
{
	int	i;
	int	max_width;

	i = -1;
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
		error("Error\nMissing map in .cub file!");
	d()->hex_ceiling = get_color_rgb(d()->map_c);
	d()->hex_floor = get_color_rgb(d()->map_f);
	init_map(max_width, nlines - d()->map_h);
}

void	parse_map(char **av)
{
	int	fd;
	int	fd2;
	int	i;

	fd = open(av[1], O_RDONLY, 0700);
	if (fd < 0)
		error("Error\nCouldn't open map");
	allocate_maplines(fd);
	close(fd);
	fd2 = open(av[1], O_RDONLY, 0700);
	if (fd2 < 0)
		error("Error\nCouldn't re-open map");
	i = copy_full_map_file(fd2);
	close(fd2);
	load_map_header(i);
	load_map_body();
	//map_print();
	map_flood_fill((int)d()->player_x / 64, (int)d()->player_y / 64, \
d()->map, d()->map_h + 1);
}
