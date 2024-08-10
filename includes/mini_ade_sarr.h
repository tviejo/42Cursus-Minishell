/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ade_sarr.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:17:03 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/08/10 02:13:22 by ade-sarr         ###   ########.fr       */
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

typedef struct s_printcmdtree
{
	int			targetdepth;
	int			fd;
	t_operator	*ope;
	int			child_xpos;
	int			branch_xpos;
	bool		prnbranch;
}	t_printcmdtree;

char	*ft_strjoin2(char const *s1, char const *s2);
char	*ft_stradd(char *s, char const *toadd);
char	*ft_straddchar(char *s, char const c);
char	*ft_int2str(int n);
void	print_char_xtimes(int fd, char c, int times);
void	print_str_xtimes(int fd, char *s, int times);

#endif