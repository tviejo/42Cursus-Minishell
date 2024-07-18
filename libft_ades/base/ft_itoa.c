/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:03:50 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/06/04 01:57:31 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/* Ecrit dans <buf> la representation en base <base> de <nbr>.
 * Attention : n'ajoute PAS de caractere terminal '\0' à la fin.
 * Renvoie un pointeur sur le caractere suivant le dernier chiffre.
*/
static char	*int2str(int nbr, unsigned int base, char *buf)
{
	unsigned int	unbr;
	char			c;

	unbr = nbr;
	if (nbr < 0)
	{
		*buf++ = '-';
		unbr = -nbr;
	}
	if (unbr >= base)
		buf = int2str(unbr / base, base, buf);
	unbr %= base;
	if (unbr < 10)
		c = '0' + unbr;
	else
		c = 'a' + unbr - 10;
	*buf++ = c;
	return (buf);
}

/* Allocates (with malloc(3)) and returns a string
 * representing the integer received as an argument.
 * Negative numbers must be handled.
 * returns : The string representing the integer.
 *           NULL if the allocation fails.
*/
char	*ft_itoa_m(int nbr)
{
	char	buf[12];
	char	*bufend;
	char	*snbr;

	bufend = int2str(nbr, 10, buf);
	*bufend = '\0';
	snbr = malloc(bufend - buf + 1);
	if (snbr == NULL)
		return (NULL);
	ft_strlcpy(snbr, buf, 12);
	return (snbr);
}
