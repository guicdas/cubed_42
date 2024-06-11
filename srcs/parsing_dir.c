/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:46:55 by mneves-l          #+#    #+#             */
/*   Updated: 2024/06/11 14:57:57 by gcatarin         ###   ########.fr       */
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
		if (ft_is_onlyspace(tmp) == 1)
		{
			temp = clean_string(tmp, 0, 0);
			d()->full_map[n_lines] = temp;
			n_lines++;
		}
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
	while (++i < nlines)
	{
		if (check_for_element(d()->full_map[i]) == 2)
			d()->map_h++;
		if (max_width < ft_strlen(d()->full_map[i]))
			max_width = ft_strlen(d()->full_map[i]);
	}
	if (!d()->map_h)
		error("Error\nMissing map in .cub file!\n");
	init_map(max_width, nlines - d()->map_h);
}

int	check_for_element(char *s)
{
	if (s && *s)
	{
		while (ft_isspace(*s) == 1)
			(*s)++;
		if (*s == 'N')
			clean_info('N', s);
		else if (*s == 'S')
			clean_info('S', s);
		else if (*s == 'W')
			clean_info('W', s);
		else if (*s == 'E')
			clean_info('E', s);
		else if (*s == 'F')
			d()->map_f = limits_colors(s);
		else if (*s == 'C')
			d()->map_c = limits_colors(s);
		else if (*s == '1')
			return (2);
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
	map_flood_fill(d()->player_x, d()->player_y, d()->map, d()->map_h);
}
