/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:32:04 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/08 19:02:24 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	if (n < 1)
		return ;
	while (n-- >= 1)
		((char *)s)[i++] = '\0';
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;
	size_t	total_mem;

	total_mem = nmemb * size;
	if (total_mem && (total_mem / size) != nmemb)
		return (NULL);
	result = malloc(total_mem);
	if (!result)
		return (NULL);
	ft_bzero(result, total_mem);
	return (result);
}

void	draw_vertical_line(int x, int start, int end, int color)
{
	while (start < end)
	{
		mlx_pixel_put(d()->mlx, d()->win_ptr, start, x, color);
		start += 2;
	}
}

int	put_b_nbr(unsigned long long nbr, char *b, size_t bs)
{
	int	i;

	i = 0;
	if (nbr >= bs)
		i = put_b_nbr((nbr / bs), b, bs);
	i *= 10;
	return (i + (b[nbr % bs] - 48));
}

char	*convert(long long n, char *str, int bs, char *b)
{
	if (n < 0)
	{
		n = -n;
		*str++ = '-';
	}
	if (n >= bs)
		str = convert(n / bs, str, bs, b);
	*str++ = b[n % bs];
	*str = 0;
	return (str);
}

char	*ft_itoa(long long n, int bs, char *b)
{
	static char	s[100];

	convert(n, s, bs, b);
	return (s);
}
