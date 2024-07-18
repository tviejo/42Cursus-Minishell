/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:39:05 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/08 20:39:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str_nbr.h"

/* Ecrit dans <buf> la representation en base <base> de <nbr>.
 * Attention : n'ajoute PAS de caractere terminal '\0' à la fin.
 * Renvoie un pointeur sur le caractere suivant le dernier chiffre.
*/
/*char	*int2str(int nbr, unsigned int base, char *buf)
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
}*/

t_uint	int2str_init(int nbr, t_i2s_fmt *fmt, char **buf)
{
	t_uint	unbr;

	unbr = nbr;
	fmt->isnegative = nbr < 0;
	if (fmt->signljust)
		i2s_print_sign(fmt, buf);
	if (fmt->isnegative)
		unbr = -nbr;
	fmt->nbr = unbr;
	return (unbr);
}

/* Conversion d'un entier en sa représentation en base <fmt->base> dans <buf>.
 * Ajoute des caractères <fmt->padchar> devant si nécessaire pour écrire
 * au moins <fmt->minlen> caractères dans <buf>.
 * Attention : lors du premier appel <d> DOIT valoir 1.
 * Attention : n'ajoute PAS de caractere terminal '\0' à la fin.
 * Renvoie un pointeur sur la position suivant le dernier chiffre/caractère.
*/
char	*int2str_ex(int nbr, int d, t_i2s_fmt *fmt, char *buf)
{
	bool	many_digits;
	t_uint	unbr;

	unbr = nbr;
	if (d == 1)
		unbr = int2str_init(nbr, fmt, &buf);
	many_digits = unbr >= fmt->base;
	if (many_digits)
		buf = int2str_ex(unbr / fmt->base, d + 1, fmt, buf);
	else
		i2s_first_digit_reached(fmt, d);
	if (many_digits && fmt->sepfreq && (d % fmt->sepfreq == 0))
		*buf++ = fmt->sepchar;
	if (!many_digits && !fmt->leftjust)
		buf = i2s_padding(fmt, buf);
	if (!many_digits && !fmt->signljust)
		i2s_print_sign(fmt, &buf);
	if (!many_digits && fmt->prefix)
		buf += ft_strcpylen(buf, fmt->prefix);
	if (!many_digits && fmt->precision_nbpad > 0)
		buf = i2s_precision_padding(fmt, buf);
	write_digit(unbr % fmt->base, fmt, &buf);
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
char	*int2str(int nbr, int base, int minlen, char *buf)
{
	t_i2s_fmt	fmt;

	i2sfmt_set(&fmt, base, minlen, 0);
	return (int2str_ex(nbr, 1, &fmt, buf));
}

/* Conversion d'un entier en sa representation en base <base> dans <buf>.
 * Ajoute des espaces devant si nécessaire pour avoir <minlen> caractères.
 * base : base ou valeur de retour de i2s_base()
 * minlen : long. mini ou valeur de retour de is2_len() ou i2s_len_j()
*/
char	*ft_itoa(int nbr, int base, int minlen, char *buf)
{
	*int2str(nbr, base, minlen, buf) = '\0';
	return (buf);
}

/* Conversion d'un entier en sa représentation en base <fmt->base> dans <buf>.
 * Ajoute des caractères <fmt->padchar> devant si nécessaire pour écrire
 * au moins <fmt->minlen> caractères dans <buf>.
*/
char	*ft_itoa_ex(int nbr, t_i2s_fmt *fmt, char *buf)
{
	*int2str_ex(nbr, 1, fmt, buf) = '\0';
	return (buf);
}
