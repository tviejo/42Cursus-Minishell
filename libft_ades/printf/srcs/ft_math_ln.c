/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_ln.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:13:00 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/03/28 12:15:00 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str_nbr.h"

static double	_sqrt(double x)
{
	double	a;
	double	b;
	double	m;

	m = 1.0;
	while (x >= 2.0)
	{
		x *= 0.25;
		m *= 2.0;
	}
	while (x < 0.5)
	{
		x *= 4.0;
		m *= 0.5;
	}
	a = x;
	b = 1.0 - x;
	a *= 1.0 + 0.5 * b;
	b *= 0.25 * (3.0 + b) * b;
	while (b >= 1.0E-15)
	{
		a *= 1.0 + 0.5 * b;
		b *= 0.25 * (3.0 + b) * b;
	}
	return (a * m);
}

double	ft_sqrt(double x)
{
	if (x == 0.0)
		return (0.0);
	else
		return (_sqrt(x));
}

static double	_ln_inner_loop(double x)
{
	double	i;
	double	xp;
	double	quotient;
	double	dl;

	i = 2.0;
	xp = x * x;
	quotient = (xp / i);
	dl = x - quotient;
	while (1.0E-15 < quotient)
	{
		i++;
		xp *= x;
		dl += (xp / i);
		i++;
		xp *= x;
		quotient = (xp / i);
		dl -= quotient;
	}
	return (dl);
}

double	ft_ln(double x)
{
	double	signe;
	double	fois;
	double	ajout;

	signe = 1.0;
	fois = 1.0;
	ajout = 0.0;
	if (x <= 0.0)
		return (0.0);
	if (x < 1.0)
	{
		signe = -1.0;
		x = 1.0 / x;
	}
	while (x >= 10.0)
	{
		x /= 10.0;
		ajout += 2.302585092994046;
	}
	while (x >= 1.1)
	{
		x = ft_sqrt(x);
		fois *= 2;
	}
	return ((_ln_inner_loop(x - 1.0) * fois + ajout) * signe);
}

void	test_ft_ln(void)
{
	double	i;

	i = 0.0;
	while (i <= 2.0)
	{
		ft_printf("[ft_printf] ln(%f) = %f\n", i, ft_ln(i));
		i += 0.05;
	}
	i = 10.0;
	ft_printf("[ft_printf] ln(%f) = %f\n", i, ft_ln(i));
}
