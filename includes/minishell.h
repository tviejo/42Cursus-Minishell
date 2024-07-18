/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:17:18 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/18 00:06:37 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "mini_tviejo.h"
# include "mini_ade_sarr.h"

enum e_nodetype
{
	nt_command,
	nt_infile,
	nt_here_doc,
	nt_out_truncate,
	nt_out_append,
	nt_pipe,
	nt_OR,
	nt_AND,
};

typedef struct s_cmdtree
{
	enum e_nodetype		type;
	char				**argument;
	struct s_cmdtree	*left;
	struct s_cmdtree	*right;
}	t_command_tree;

typedef t_command_tree	t_cmdtree;

#endif