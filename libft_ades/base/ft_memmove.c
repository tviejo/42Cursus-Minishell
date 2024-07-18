/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:46:34 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/21 01:49:07 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*buffer;
	unsigned char	*buf;
	unsigned char	*dst;
	int				nb;

	buffer = malloc(n);
	if (buffer == NULL)
		return (NULL);
	buf = buffer;
	nb = n;
	while (nb--)
		*buf++ = *(unsigned char *)src++;
	buf = buffer;
	nb = n;
	dst = dest;
	while (nb--)
		*dst++ = *buf++;
	free(buffer);
	return (dest);
}
*/

void	*ft_memmove(void *dest, const void *sourc, size_t n)
{
	const unsigned char	*src;
	unsigned char		*dst;

	src = sourc;
	dst = dest;
	if (dst == src)
		return (dest);
	if (dst < src)
		while (n--)
			*dst++ = *src++;
	else
	{
		src += n - 1;
		dst += n - 1;
		while (n--)
			*dst-- = *src--;
	}
	return (dest);
}
