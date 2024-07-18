/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:51:25 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/05/27 09:51:25 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str_nbr.h"
#include <unistd.h>
#include <stdarg.h>

int	print_c(int c, t_format_id *fid)
{
	const char	str[] = {c, '\0'};
	int			count;

	fid->max_width = -1;
	count = 0;
	if (c == 0 && fid->min_width > 0)
		fid->min_width--;
	if (c == 0 && fid->left_justify)
		count += write(1, str, 1);
	count += print_s((char *)str, fid);
	if (c == 0 && !fid->left_justify)
		count += write(1, str, 1);
	return (count);
}

int	print_p(uint64_t ptr64, t_format_id *fid, t_i2s_fmt *fmt, char *sbuf)
{
	if (ptr64 == 0)
	{
		fid->max_width = -1;
		return (print_s("(nil)", fid));
	}
	return (print(ft_ultoa_ex(ptr64, get_i2s_fmt(fid, fmt), sbuf)));
}

int	print_arg(t_format_id *fid, va_list args, char *sbuf)
{
	const int	type = fid->type;
	t_i2s_fmt	fmt;

	if (type == 'c')
		return (print_c(va_arg(args, int), fid));
	if (type == 's')
		return (print_s(va_arg(args, char *), fid));
	if (type == 'd' || type == 'i')
		return (print(ft_itoa_ex(va_arg(args, int),
					get_i2s_fmt(fid, &fmt), sbuf)));
	if (type == 'u' || type == 'x' || type == 'X')
		return (fmt.nbr = va_arg(args, t_uint),
			print(ft_utoa_ex(fmt.nbr, get_i2s_fmt(fid, &fmt), sbuf)));
	if (type == 'p')
		return (print_p(va_arg(args, uint64_t), fid, &fmt, sbuf));
	if (type == 'l' || type == 'b')
		return (print(ft_ltoa_ex(va_arg(args, long),
					get_i2s_fmt(fid, &fmt), sbuf)));
	if (type == 'f')
		return (print_f(va_arg(args, double), fid, sbuf));
	if (type == 'F')
		return (print_cap_f(args, sbuf));
	if (type == '%')
		return (write(1, "%", 1));
	return (0);
}
/*	if (type == 'p')
		return (print(ft_ultoa_ex(va_arg(args, size_t),
				get_i2s_fmt(fid, &fmt), sbuf)));*/
/*	if (type == 'P')
		return (print(ft_ultoa(va_arg(args, size_t), 16,
					i2s_len(2 * sizeof(size_t), '0'), sbuf)));*/

/*
 * ft_printf est un clone de printf
 * Format identifier : %[flags][min width][.max width/precision][B<base>]<type>
 *	flags:	- : left justify
 *			0 : field is padded with 0's instead of blanks
 *			+ : sign of number always O/P
 *			blank : positive values begin with a blank
			#x/#X : 0x/0X prefix added to non-zero values
 * <format> : chaine integrant les types suivants:
 *    'c' : char
 *    's' : string (char *)
 *    'd' ou 'i' : decimal (int) ; pour i (expl: %B12i), option B<base> possible
 *    'b' : binaire (long)
 *    'x','X' : hexadecimal (long)
 *    'u' : uint64_t (unsigned long)
 *    'l' : long int
 *    'p' : pointeur (32-bit ou 64-bit, affichage en hexa)
 *    'f' : double
 *    'F' : double avec base et nbdigits fournis par arguments
 * 
 * NB : .precision avec un entier (%d) definit un premier niveau de padding a
 *		gauche (ajoute des zeros devant le signe du nombre) auquel viendra
 *		s ajouter le second padding de min width (dans ce cas ce second padding
 *		utilisera toujours le car espace, le zero est ignore). Si .precision est
 *		absent alors le padding de min width utilisera le car espace ou le zero.
*/
int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (format == NULL)
		return (-1);
	va_start(args, format);
	count = ft_vprintf(format, args);
	va_end(args);
	return (count);
}

int	ft_vprintf(const char *format, va_list args)
{
	int			count;
	char		sbuf[PRINTF_ARG_BUFFER_SIZE];
	const char	*form0;
	bool		new_format_id;
	t_format_id	fid;

	if (format == NULL)
		return (-1);
	count = 0;
	while (*format)
	{
		form0 = format;
		while (*format && *format != '%')
			format++;
		new_format_id = (*format == '%');
		if (format > form0)
			count += write(1, form0, format - form0);
		if (new_format_id)
		{
			format = parse_format_id(++format, &fid);
			count += print_arg(&fid, args, sbuf);
		}
	}
	return (count);
}
