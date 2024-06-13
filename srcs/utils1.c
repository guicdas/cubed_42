/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcatarin <gcatarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 19:04:48 by gcatarin          #+#    #+#             */
/*   Updated: 2024/06/13 13:17:44 by gcatarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cubed.h"

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

static char	*convert(long long n, char *str, int bs, char *b)
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

char	*clean_string(char *s, int i, int flag)
{
	int		start;
	int		end;
	char	*new;

	if (flag == 1 && s[i])
	{
		while (ft_isspace(s[i]) == 1 || s[i] == '\n')
			i++;
		start = i;
	}
	else
		start = 0;
	i = ft_strlen(s) - 1;
	while ((ft_isspace(s[i]) == 1 || s[i] == '\n') && i > 0)
		i--;
	new = ft_calloc(sizeof(char *), i - start + 1);
	end = i + 1;
	if (i > start)
		new[end] = '\0';
	else
		new[0] = '\0';
	i = 0;
	while (start < end)
		new[i++] = s[start++];
	return (new);
}
