/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i2s_padding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:39:05 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/08 20:39:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_str_nbr.h"

int	get_signlen(t_i2s_fmt *fmt)
{
	if (fmt->isnegative)
	{
		if (fmt->strneg)
			return (ft_strlen(fmt->strneg));
		return (1);
	}
	if (fmt->strpos)
		return (ft_strlen(fmt->strpos));
	return (0);
}

int	get_dpos_and_put_first_sep_incase(t_i2s_fmt *fmt, int length, char **buf)
{
	int	dpos;

	if (!fmt->signljust)
		length = fmt->minlen;
	dpos = length - length / (fmt->sepfreq + 1);
	if (fmt->leftjust)
		dpos = 300 * fmt->sepfreq;
	if ((length % (fmt->sepfreq + 1) == 0) || fmt->leftjust)
		*(*buf)++ = fmt->sepchar;
	return (dpos);
}

char	*i2s_padding(t_i2s_fmt *fmt, char *buf)
{
	char		*bufmax;
	const bool	seppad = fmt->seppad && fmt->sepfreq;
	const int	length = fmt->minlen - get_signlen(fmt);
	int			dpos;

	bufmax = buf + length - fmt->nbdigits - ft_strlen(fmt->prefix);
	if (fmt->sepfreq)
		bufmax -= (fmt->nbdigits - 1) / fmt->sepfreq;
	if (seppad && buf < bufmax)
		dpos = get_dpos_and_put_first_sep_incase(fmt, length, &buf);
	while (buf < bufmax)
	{
		*buf++ = fmt->padchar;
		if (seppad && (--dpos % fmt->sepfreq == 0) && buf < bufmax)
			*buf++ = fmt->sepchar;
	}
	return (buf);
}

char	*i2s_precision_padding(t_i2s_fmt *fmt, char *buf)
{
	int	nbpad;

	nbpad = fmt->precision_nbpad;
	while (nbpad-- > 0)
		*buf++ = '0';
	return (buf);
}

void	i2s_first_digit_reached(t_i2s_fmt *fmt, int nbdigits)
{
	fmt->precision_nbpad = fmt->printf_precision - nbdigits;
	if (fmt->precision_nbpad < 0)
		fmt->precision_nbpad = 0;
	fmt->nbdigits = nbdigits + fmt->precision_nbpad;
	if (fmt->nbr == 0 && fmt->printf_precision == 0)
		fmt->nbdigits--;
}
