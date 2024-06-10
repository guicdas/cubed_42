/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnuncio- <jnuncio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:46:55 by mneves-l          #+#    #+#             */
/*   Updated: 2024/06/10 20:17:58 by jnuncio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

//Save and check every imput before the game starts
void	parsing(char **av)
{
	int	fd;
	int	fd2;

	fd = open(av[1], O_RDONLY, 0700);
	if (fd < 0)
		error("Error\nCouldn't open map\n");
	fd2 = open(av[1], O_RDONLY, 0700);
	if (fd2 < 0)
		error("Error\nCouldn't open map\n");
	load_map(fd, fd2);
	map_check_matriz();
	map_flood_fill(d()->player_x, d()->player_y, d()->map, d()->map_h);
}

static int	get_full_map(int fd, int fd2)
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
	close(fd);
	temp = ft_calloc(sizeof(char **), n_lines);
	if (!temp)
		error("Error\nFailed to allocate full_map.\n");
	d()->full_map = temp;
	while (1)
	{
		tmp = get_next_line(fd2);
		if (tmp == NULL)
			break ;
		tmp = clean_string(tmp, 0, 0);
		if (ft_strlen(tmp) != 0)
			d()->full_map[i++] = tmp;
		free(tmp);
	}
	d()->full_map[i] = NULL;
	close(fd2);
	return (n_lines);
}

void	load_map(int fd, int fd2)
{
	int		i;
	int		n_lines;
	char	**temp;

	n_lines = get_full_map(fd, fd2);
	i = -1;
	while (++i < n_lines)
	{
		if (check_for_element(d()->full_map[i]) == 2)
			d()->map_h++;
	}
	if (d()->map_h)
	{
		temp = ft_calloc(sizeof(char **), d()->map_h);
		if (!temp)
			error("Error\nFailed to allocate map.\n");
		d()->map = temp;
		i = n_lines - d()->map_h;
	}
	while (d()->full_map[++i] != NULL)
		d()->map[i] = d()->full_map[i];
	d()->map[i] = NULL;
}

int	check_for_element(char *s)
{
	if (s && s[0])
	{
		while (s[0] == ' ' || s[0] == '\t')
			*s++;
		if (s[0] == 'N' && s[1] == 'O')
			d()->map_no = s;
		else if (s[0] == 'S' && s[1] == 'O')
			d()->map_so = s;
		else if (s[0] == 'W' && s[1] == 'E')
			d()->map_we = s;
		else if (s[0] == 'E' && s[1] == 'A')
			d()->map_ea = s;
		else if (s[0] == 'F')
		{
			if (!d()->map_f)
				d()->map_f = limits_colors(s);
		}
		else if (s[0] == 'C')
		{
			if (!d()->map_c)
				d()->map_c = limits_colors(s);
		}
		else if (s[0] == '1')
			return (2);
		return (1);
	}
	return (0);
}

//cut white spaces from the begginig and/or from the end of a string
char	*clean_string(char *s, int i, int flag)
{
	int		start;
	int		end;
	char	*new;

	if (flag == 1)
	{
		while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		start = i;
	}
	else
		start = 0;
	i = ft_strlen(s) - 1;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i--;
	new = ft_calloc(sizeof(char *), i - start + 1);
	end = i;
	new[end + 1] = '\0';
	i = 0;
	while (start <= end)
		new[i++] = s[start++];
	return (new);
}
