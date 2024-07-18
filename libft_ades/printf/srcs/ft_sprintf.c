/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:39:05 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/08 20:39:08 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdarg.h>
#include "ft_str_nbr.h"

char	*sprint_cap_f(va_list args, char *sbuf)
{
	const double	nbr = va_arg(args, double);
	const int		base = va_arg(args, int);
	const int		nbdigits = va_arg(args, int);

	return (double2str(nbr, base, nbdigits, sbuf));
}

char	*sprint_s(char *str, t_format_id *fid, char *buffer)
{
	int	length;
	int	padlen;

	if (str == NULL)
	{
		str = "";
		if (fid->max_width == -1 || fid->max_width >= 6)
			str = "(null)";
	}
	length = ft_strlen(str);
	padlen = fid->min_width - length;
	if (fid->max_width != -1 && fid->max_width < length)
		length = fid->max_width;
	if (fid->left_justify)
		buffer += ft_strlencpy(buffer, str, length + 1);
	while (padlen-- > 0)
		*buffer++ = ' ';
	if (!fid->left_justify)
		buffer += ft_strlencpy(buffer, str, length + 1);
	return (buffer);
}

char	*sprint_arg(t_format_id *fid, va_list args, char *sbuf)
{
	const int	type = fid->type;
	t_i2s_fmt	fmt;

	if (type == 'c')
		return (sprint_c(va_arg(args, int), fid, sbuf));
	if (type == 's')
		return (sprint_s(va_arg(args, char *), fid, sbuf));
	if (type == 'd' || type == 'i')
		return (int2str_ex(va_arg(args, int), 1,
				get_i2s_fmt(fid, &fmt), sbuf));
	if (type == 'u' || type == 'x' || type == 'X')
		return (fmt.nbr = va_arg(args, t_uint),
			uint2str_ex(fmt.nbr, 1, get_i2s_fmt(fid, &fmt), sbuf));
	if (type == 'p')
		return (sprint_p(va_arg(args, uint64_t), fid, &fmt, sbuf));
	if (type == 'l' || type == 'b')
		return (long2str_ex(va_arg(args, long), 1,
				get_i2s_fmt(fid, &fmt), sbuf));
	if (type == 'f')
		return (sprint_f(va_arg(args, double), fid, sbuf));
	if (type == 'F')
		return (sprint_cap_f(args, sbuf));
	if (type == '%')
		return (*sbuf = '%', sbuf + 1);
	return (sbuf);
}

int	ft_sprintf(char *buffer, const char *format, ...)
{
	va_list	args;
	int		count;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	count = ft_vsprintf(buffer, format, args);
	va_end(args);
	return (count);
}

int	ft_vsprintf(char *buffer, const char *format, va_list args)
{
	const char	*buf0 = buffer;
	const char	*form0;
	bool		new_format_id;
	t_format_id	fid;

	if (format == NULL)
		return (-1);
	while (*format)
	{
		form0 = format;
		while (*format && *format != '%')
			format++;
		new_format_id = (*format == '%');
		if (format > form0)
			buffer += ft_strlencpy(buffer, form0, format - form0 + 1);
		if (new_format_id)
		{
			format = parse_format_id(++format, &fid);
			buffer = sprint_arg(&fid, args, buffer);
		}
	}
	*buffer = '\0';
	return (buffer - buf0);
}
