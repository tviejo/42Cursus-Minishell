/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:46:49 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/22 16:24:34 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const void	*dest0 = dest;

	if (dest == src)
		return (dest);
	while (n--)
		*(unsigned char *)dest++ = *(unsigned char *)src++;
	return ((void *)dest0);
}
