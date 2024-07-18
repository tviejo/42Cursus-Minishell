/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ade_sarr.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:17:03 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/18 18:46:25 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_ADE_SARR_H
# define MINI_ADE_SARR_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Pile générique (éléments de type void *) mise en oeuvre à l'aide d'un tableau
*/
typedef struct s_stack
{
	int		nb_max_elems;
	void	**top;
	void	**elems;
}	t_stack;

#endif