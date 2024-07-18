/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:13:00 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/18 12:15:00 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

double	powerd(double x, int n)
{
	double	pow;

	if (n < 0)
		return (powerd(1.0 / x, -n));
	if (n == 0)
		return (1);
	pow = x;
	while (--n)
		pow *= x;
	return (pow);
}

long long	power(long long x, int n)
{
	long long	pow;

	if (n < 0)
		return (0);
	if (n == 0)
		return (1);
	pow = x;
	while (--n)
		pow *= x;
	return (pow);
}

unsigned long long	factorial(int n)
{
	unsigned long long	fact;

	if (n < 0)
		return (0);
	if (n < 2)
		return (1);
	fact = n;
	while (--n > 1)
		fact *= n;
	return (fact);
}

unsigned long long	arrangement(int p, int n)
{
	unsigned long long	arr;

	if (p > n)
		return (0);
	if (p == 0)
		return (1);
	arr = n;
	p = n - p;
	while (--n > p)
		arr *= n;
	return (arr);
}

unsigned long long	combination(int p, int n)
{
	return (arrangement(p, n) / factorial(p));
}
