/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double2str_hlp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:39:05 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/08 20:39:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include "ft_str_nbr.h"

/* Ecrit dans <buf> si valeur spéciale trouvée pour <nbr>
 * Renvoie la position de fin de chaine si valeur spéciale
 * sinon renvoie NULL
*/
char	*dblspecialvals(double nbr, char *buf)
{
	const uint64_t	nbr64 = *(uint64_t *)&nbr;
	const int		exp = (int)((nbr64 >> 52) & 0x7FF);
	const uint64_t	fract = nbr64 & 0x000fffffffffffffu;
	char			*pbuf;

	pbuf = buf;
	if (exp == 0x7ff && fract != 0)
		pbuf += ft_strcpylen(pbuf, "NaN");
	else if ((int)(nbr64 >> 63))
		*pbuf++ = '-';
	if (exp == 0x7ff && fract == 0)
		pbuf += ft_strcpylen(pbuf, "inf");
	if (exp == 0 && fract == 0)
		pbuf += ft_strcpylen(pbuf, "0.0");
	if (exp == 0 && fract != 0)
		pbuf += ft_strcpylen(pbuf, "subnormal");
	if (pbuf > buf && pbuf[-1] != '-')
		return (pbuf);
	return (NULL);
}

/* Dernière partie de dblraw2str():
 * analyse exposant base 2 / special number
*/
char	*dblraw2str_exp(double nbr, int exp, char *buf)
{
	char	*special;

	buf += ft_strcpylen(buf, " e:");
	buf = int2str(exp, 16, i2s_len(3, '0'), buf);
	buf += ft_strcpylen(buf, " (");
	special = dblspecialvals(nbr, buf);
	if (special)
		return (special + ft_strcpylen(special, ")"));
	buf += ft_strcpylen(buf, "2^");
	buf = int2str(exp - 1023, 10, 0, buf);
	buf += ft_strcpylen(buf, ")");
	return (buf);
}

/* Donne la representation interne d'un double (signe/exposant/fract.)
 * exple pour  3.0  : 400.8[0.10000000000.1000] 0000 0000 0000  s:+ e:400 (2^1)
 * exple pour -1.75 : bff.c[1.01111111111.1100] 0000 0000 0000  s:- e:3ff (2^0)
 * exple pour +inf  : 7ff.0[0.11111111111.0000] 0000 0000 0000  s:+ e:7ff (+inf)
 * https://en.wikipedia.org/wiki/IEEE_754
 * https://en.wikipedia.org/wiki/Double-precision_floating-point_format
*/
char	*dblraw2str(double nbr, char *buf)
{
	static const char	*csign = "+-";
	const uint64_t		nbr64 = *(uint64_t *)&nbr;
	char *const			buf0 = buf;
	t_i2s_fmt			fmt;

	buf = int2str(nbr64 >> 52, 16, i2s_len(3, '0'), buf);
	*buf++ = '.';
	buf = int2str((nbr64 >> 48) & 0xf, 16, 0, buf);
	*buf++ = '[';
	buf = int2str(nbr64 >> 63, 2, 0, buf);
	*buf++ = '.';
	buf = int2str((nbr64 >> 52) & 0x7ff, 2, i2s_len(11, '0'), buf);
	*buf++ = '.';
	buf = int2str((nbr64 >> 48) & 0xf, 2, i2s_len(4, '0'), buf);
	*buf++ = ']';
	*buf++ = ' ';
	i2sfmt_set(&fmt, 16, i2s_len(14, '0'), i2s_sep(4, ' ', true));
	buf = ulong2str_ex(nbr64 & 0x0000ffffffffffffu, 1, &fmt, buf);
	buf += ft_strcpylen(buf, "  s:");
	*buf++ = csign[nbr64 >> 63];
	dblraw2str_exp(nbr, (nbr64 >> 52) & 0x7ff, buf);
	return (buf0);
}
