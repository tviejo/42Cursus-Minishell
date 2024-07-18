/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf3.c                                       :+:      :+:    :+:   */
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

int	print(char *str)
{
	return (write(1, str, ft_strlen(str)));
}

int	print_s(char *str, t_format_id *fid)
{
	int	length;
	int	padlen;
	int	count;

	if (str == NULL)
	{
		str = "";
		if (fid->max_width == -1 || fid->max_width >= 6)
			str = "(null)";
	}
	count = 0;
	length = ft_strlen(str);
	if (fid->max_width != -1 && fid->max_width < length)
		length = fid->max_width;
	padlen = fid->min_width - length;
	if (fid->left_justify)
		count += write(1, str, length);
	while (padlen-- > 0)
		count += write(1, " ", 1);
	if (!fid->left_justify)
		count += write(1, str, length);
	return (count);
}

int	print_cap_f(va_list args, char *sbuf)
{
	const double	nbr = va_arg(args, double);
	const int		base = va_arg(args, int);
	const int		nbdigits = va_arg(args, int);

	return (print(ft_ftoa(nbr, base, nbdigits, sbuf)));
}

int	print_f(double nbr, t_format_id *fid, char *sbuf)
{
	if (fid->base != 0)
		return (print(ft_ftoa(nbr, fid->base, fid->precision, sbuf)));
	else
		return (print(ft_ftoa(nbr, 10, fid->precision, sbuf)));
}
