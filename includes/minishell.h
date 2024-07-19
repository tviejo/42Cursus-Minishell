/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tviejo <tviejo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:17:18 by ade-sarr          #+#    #+#             */
/*   Updated: 2024/07/19 10:15:21 by tviejo           ###   ########.fr       */
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

int			ft_export(t_command_tree *tree, t_exec *exec);
int			ft_cd(t_command_tree *tree, t_exec *exec);
int			ft_env(t_exec *exec);
int			ft_pwd(t_exec *exec);
int			ft_unset(t_command_tree *tree, t_exec *exec);
int			ft_echo(t_command_tree *tree);
int			find_builtin(t_command_tree *tree);
int			exec_builtin(t_command_tree *tree, t_exec *exec);

#endif