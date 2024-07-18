/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 21:42:58 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/06/10 10:39:55 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str_nbr.h"
#include <stdbool.h>
#include <unistd.h>

/*int	ft_strlen(const char *str)
{
	const char	*s = str;

	if (!str)
		return (0);
	while (*s)
		s++;
	return (s - str);
}*/

void	ft_puterrmsg(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void	ft_putstr(char *str, bool lineret)
{
	if (str)
		write(1, str, ft_strlen(str));
	if (lineret)
		write(1, "\n", 1);
}

/*unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size)
{
	int	n;
	int	l;

	l = 0;
	if (size > 0)
	{
		n = size - 1;
		while (*src && n)
		{
			*dest++ = *src++;
			n--;
			l++;
		}
		*dest = '\0';
	}
	while (*src++)
		l++;
	return (l);
}*/

char	*ft_strncpy(char *dest, const char *src, unsigned int n)
{
	char	*dst;

	if (!src || !dest)
		return (dest);
	dst = dest;
	while (*src && n)
	{
		*dst++ = *src++;
		n--;
	}
	while (n)
	{
		*dst++ = '\0';
		n--;
	}
	return (dest);
}
