/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i2s_format2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:39:05 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/08 20:39:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_str_nbr.h"

/* Renseigne une struct t_i2sfmt
 * strneg : chaine à afficher pour le signe si nombre négatif ("-" si NULL)
 * strpos : chaine à afficher pour le signe si nombre positif (rien si NULL)
 * Renvoie la longueur maximale de : (strneg ou strpos) et prefix
*/
int	i2sfmt_setstr(t_i2s_fmt *fmt, char *strneg, char *strpos, char *prefix)
{
	int	strneglen;
	int	strposlen;

	fmt->strneg = strneg;
	fmt->strpos = strpos;
	fmt->prefix = prefix;
	strneglen = 1;
	if (strneg)
		strneglen = ft_strlen(strneg);
	strposlen = ft_strlen(strpos);
	if (strneglen > strposlen)
		return (strneglen + ft_strlen(prefix));
	return (strposlen + ft_strlen(prefix));
}

void	i2s_print_sign(t_i2s_fmt *fmt, char **buf)
{
	if (fmt->isnegative)
	{
		if (fmt->strneg)
			*buf += ft_strcpylen(*buf, fmt->strneg);
		else
			*(*buf)++ = '-';
	}
	else if (fmt->strpos)
		*buf += ft_strcpylen(*buf, fmt->strpos);
}

char	get_asciidigit(int digit, bool majuscule)
{
	static const char *const	minusc = "0123456789abcdefghijklmnopqrstuvwxyz";
	static const char *const	majusc = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (majuscule)
		return (majusc[digit]);
	return (minusc[digit]);
}

void	write_digit(int digit, t_i2s_fmt *fmt, char **buffer)
{
	if (!(fmt->nbr == 0 && fmt->printf_precision == 0))
		*(*buffer)++ = get_asciidigit(digit, fmt->capitdgt);
}
