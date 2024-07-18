/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 00:41:40 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/06/04 03:00:25 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_ades.h"
#include <stdlib.h>

int	main(void)
{
	char	*line;

	line = get_next_line(0);
	ft_putstr_fd(line, 1);
	ft_printf("%s", line);
	free(line);
}
