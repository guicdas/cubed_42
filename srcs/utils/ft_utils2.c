/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:32:04 by gcatarin          #+#    #+#             */
/*   Updated: 2025/05/01 01:38:36 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cubed.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	write(fd, "\033[0;31m", ft_strlen("\033[0;31m"));
	while (s[i])
	{
		write(fd, &s[i], 1);
		if (s[i] == '\n')
			write(fd, "\033[0m", ft_strlen("\033[0m"));
		i++;
	}
	write(fd, "\n", 1);
}

int	ft_strlen_array(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
