/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:39:05 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/08 20:39:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include "ft_str_nbr.h"

char	*sprint_p(uint64_t ptr64, t_format_id *fid, t_i2s_fmt *fmt, char *sbuf)
{
	if (ptr64 == 0)
	{
		fid->max_width = -1;
		return (sprint_s("(nil)", fid, sbuf));
	}
	return (ulong2str_ex(ptr64, 1, get_i2s_fmt(fid, fmt), sbuf));
}

char	*sprint_c(int c, t_format_id *fid, char *buffer)
{
	const char	str[] = {c, '\0'};

	fid->max_width = -1;
	if (c == 0 && fid->min_width > 0)
		fid->min_width--;
	if (c == 0 && fid->left_justify)
		*buffer++ = 0;
	buffer = sprint_s((char *)str, fid, buffer);
	if (c == 0 && !fid->left_justify)
		*buffer++ = 0;
	return (buffer);
}

char	*sprint_f(double nbr, t_format_id *fid, char *sbuf)
{
	if (fid->base != 0)
		return (double2str(nbr, fid->base, fid->precision, sbuf));
	else
		return (double2str(nbr, 10, fid->precision, sbuf));
}
