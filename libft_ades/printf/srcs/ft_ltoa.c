/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:39:05 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/08 20:39:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str_nbr.h"

/*char	*long2str_ex(long nbr, int i, t_i2s_fmt *fmt, char *buf)
{
	static const char *const	digits = "0123456789abcdefghijklmnopqrstuvwxyz";
	unsigned long				unbr;

	unbr = nbr;
	if (nbr < 0)
	{
		*buf++ = '-';
		unbr = -nbr;
	}
	if (unbr >= fmt->base || i < fmt->minlen)
		buf = long2str_ex(unbr / fmt->base, i + 1, fmt, buf);
	if (fmt->sepfreq && unbr && (i % fmt->sepfreq == 0))
		*buf++ = fmt->sepchar;
	if (unbr == 0 && i > 1)
		*buf = fmt->padchar;
	else
		*buf = digits[unbr % fmt->base];
	return (buf + 1);
}*/

t_ulong	long2str_init(long nbr, t_i2s_fmt *fmt, char **buf)
{
	t_ulong	unbr;

	unbr = nbr;
	fmt->isnegative = nbr < 0;
	if (fmt->signljust)
		i2s_print_sign(fmt, buf);
	if (fmt->isnegative)
		unbr = -nbr;
	return (unbr);
}

/* Conversion d'un entier en sa représentation en base <fmt->base> dans <buf>.
 * Ajoute des caractères <fmt->padchar> devant si nécessaire pour écrire
 * au moins <fmt->minlen> caractères dans <buf>.
 * Attention : lors du premier appel <d> DOIT valoir 1.
 * Attention : n'ajoute PAS de caractere terminal '\0' à la fin.
 * Renvoie un pointeur sur la position suivant le dernier chiffre/caractère.
*/
char	*long2str_ex(long nbr, int d, t_i2s_fmt *fmt, char *buf)
{
	bool	many_digits;
	t_ulong	unbr;

	unbr = nbr;
	if (d == 1)
		unbr = long2str_init(nbr, fmt, &buf);
	many_digits = unbr >= fmt->base;
	if (many_digits)
		buf = long2str_ex(unbr / fmt->base, d + 1, fmt, buf);
	else
		fmt->nbdigits = d;
	if (many_digits && fmt->sepfreq && (d % fmt->sepfreq == 0))
		*buf++ = fmt->sepchar;
	if (!many_digits && !fmt->leftjust)
		buf = i2s_padding(fmt, buf);
	if (!many_digits && !fmt->signljust)
		i2s_print_sign(fmt, &buf);
	if (!many_digits && fmt->prefix)
		buf += ft_strcpylen(buf, fmt->prefix);
	*buf++ = get_asciidigit(unbr % fmt->base, fmt->capitdgt);
	if (d == 1 && fmt->leftjust)
		buf = i2s_padding(fmt, buf);
	return (buf);
}

/* Conversion de l'entier <nbr> dans <buf> en sa representation en base <base>.
 * Ajoute des espaces devant si nécessaire pour avoir <minlen> caractères.
 * base : base ou valeur de retour de i2s_base()
 * minlen : long. mini ou valeur de retour de is2_len() ou i2s_len_j()
 * Attention : n'ajoute PAS de caractere terminal '\0' à la fin.
 * Renvoie un pointeur sur la position suivant le dernier chiffre/caractère.
*/
char	*long2str(long nbr, int base, int minlen, char *buf)
{
	t_i2s_fmt	fmt;

	i2sfmt_set(&fmt, base, minlen, 0);
	return (long2str_ex(nbr, 1, &fmt, buf));
}

/* Conversion d'un entier en sa representation en base <base> dans <buf>.
 * Ajoute des espaces devant si nécessaire pour avoir <minlen> caractères.
 * base : base ou valeur de retour de i2s_base()
 * minlen : long. mini ou valeur de retour de is2_len() ou i2s_len_j()
*/
char	*ft_ltoa(long nbr, int base, int minlen, char *buf)
{
	*long2str(nbr, base, minlen, buf) = '\0';
	return (buf);
}

/* Conversion d'un entier en sa représentation en base <fmt->base> dans <buf>.
 * Ajoute des caractères <fmt->padchar> devant si nécessaire pour écrire
 * au moins <fmt->minlen> caractères dans <buf>.
*/
char	*ft_ltoa_ex(long nbr, t_i2s_fmt *fmt, char *buf)
{
	*long2str_ex(nbr, 1, fmt, buf) = '\0';
	return (buf);
}
