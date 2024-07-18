/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:04:54 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/22 16:47:43 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	n;
	size_t	len;

	if (size == 0)
		return (ft_strlen(src));
	len = ft_strlen(dst);
	dst += len;
	if (size > len)
	{
		n = size - len - 1;
		while (*src && n)
		{
			*dst++ = *src++;
			n--;
			len++;
		}
		*dst = '\0';
		while (*src++)
			len++;
		return (len);
	}
	n = 0;
	while (src[n])
		n++;
	return (n + size);
}
