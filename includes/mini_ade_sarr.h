/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_ade_sarr.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:17:03 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/20 10:02:16 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_ADE_SARR_H
# define MINI_ADE_SARR_H

# include "stack.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_operator
{
	char	*token;
	int		priority;
}	t_operator;

typedef struct s_parsing
{
	t_operator			*operators;
	t_stack				*pile_ope;
	t_stack				*pile_npi;
	struct s_cmdtree	*cmdtree;
	char				**splited_words;
}	t_parsing;

t_parsing			*init_parsing(void);
void				free_parsing(t_parsing *p);
struct s_cmdtree	*parse_cmdline(t_parsing *p, char *cmdline);
void				print_cmdtree(struct s_cmdtree *cmdtree, t_operator *ope,
						int depth);
void				free_cmdtree(t_parsing *p);
struct s_cmdtree	*new_node(t_parsing *p, char ***words);
int					get_node_priority(t_parsing *p, struct s_cmdtree *node);
enum e_nodetype		get_node_type(t_parsing *p, char *word);
int					get_nb_args(t_parsing *p, char **words);

#endif