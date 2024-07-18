/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:04:57 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/20 16:11:10 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	n;
	size_t	l;

	l = 0;
	if (size > 0)
	{
		n = size - 1;
		while (*src && n)
		{
			*dst++ = *src++;
			n--;
			l++;
		}
		*dst = '\0';
	}
	while (*src++)
		l++;
	return (l);
}
