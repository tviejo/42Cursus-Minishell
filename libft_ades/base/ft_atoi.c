/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:06:06 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/02 19:19:01 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digit(char c)
{
	int	digit;

	digit = -1;
	if (c >= '0' && c <= '9')
		digit = c - '0';
	if (c >= 'a' && c <= 'z')
		digit = c - 'a' + 10;
	if (c >= 'A' && c <= 'Z')
		digit = c - 'A' + 10;
	return (digit);
}

static int	str2int(const char *str, int base, char **pend)
{
	int	num;
	int	signe;
	int	digit;

	num = 0;
	signe = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = -signe;
		str++;
	}
	digit = get_digit(*str);
	while (digit >= 0 && digit < base)
	{
		num = base * num + digit;
		digit = get_digit(*++str);
	}
	if (pend)
		*pend = (char *)str;
	return (num * signe);
}

int	ft_atoi(const char *str)
{
	return (str2int(str, 10, 0));
}
