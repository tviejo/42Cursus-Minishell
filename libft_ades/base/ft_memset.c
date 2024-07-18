/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:45:56 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/22 16:21:42 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *mem, int c, size_t n)
{
	const void	*mem0 = mem;

	while (n--)
		*(unsigned char *)mem++ = (unsigned char)c;
	return ((void *)mem0);
}
