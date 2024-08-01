/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ade_sarr.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:17:03 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/01 11:40:59 by tviejo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_ADE_SARR_H
# define MINI_ADE_SARR_H

# include "stack.h"
# include "queue.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PRI_LOGIC 0
# define PRI_PIPE 1
# define PRI_REDIR 2

typedef struct s_operator
{
	char	*token;
	int		priority;
}	t_operator;

enum e_quote_state
{
	no_quote,	
	simple_quote,
	double_quote
};

char	*ft_strjoin2(char const *s1, char const *s2);
char	*ft_stradd(char *s, char const *toadd);
char	*ft_straddchar(char *s, char const c);
char	*ft_int2str(int n);

#endif