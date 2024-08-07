/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_logo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 18:47:13 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/07 23:16:19 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_minishell(void)
{
	ft_dprintf(2, "    __  ________   ___________ __  __________    __ \n");
	ft_dprintf(2, "   /  |/  /  _/ | / /  _/ ___// / / / ____/ /   / / \n");
	ft_dprintf(2, "  / /|_/ // //  |/ // / |__ |/ /_/ / __/ / /   / /  \n");
	ft_dprintf(2, " / /  / // // /|  // / ___/ / __  / /___/ /___/ /___\n");
	ft_dprintf(2, "/_/  /_/___/_/ |_/___//____/_/ /_/_____/_____/_____/\n\n");
	ft_dprintf(2, "Thomas Viejo & Aurélien de Sarrau (juillet-aout 2024)\n\n");
	return (0);
}
