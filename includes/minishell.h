/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:17:18 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/20 22:23:10 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "mini_ade_sarr.h"
# include "mini_tviejo.h"

enum	e_nodetype
{
	nt_command,
	nt_infile,
	nt_here_doc,
	nt_out_truncate,
	nt_out_append,
	nt_pipe,
	nt_OR,
	nt_AND,
	nt_open_parenth,
	nt_close_parenth,
	nt_number_of_nodetype
};

typedef struct s_cmdtree
{
	enum e_nodetype		type;
	char				**argument;
	int					nb_command;
	struct s_cmdtree	*left;
	struct s_cmdtree	*right;
}						t_command_tree;

typedef t_command_tree	t_cmdtree;

int						ft_export(t_command_tree *tree, t_exec *exec);
int						ft_cd(t_command_tree *tree, t_exec *exec);
int						ft_env(t_exec *exec);
int						ft_pwd(t_exec *exec);
int						ft_unset(t_command_tree *tree, t_exec *exec);
int						ft_echo(t_command_tree *tree);
int						find_builtin(t_command_tree *tree);
int						exec_builtin(t_command_tree *tree, t_exec *exec);
int						ft_exit(t_command_tree *tree);
char					*find_path_cmd(char **envp);
int						ft_close_error(t_command_tree *tree, t_exec *exec);
void					exec_cmd(t_command_tree *tree, t_exec *exec,
							char **argument);
int						cmd_process(char **cmd, t_command_tree *tree,
							t_exec *exec, int index);
int						calloc_pid(t_exec *exec, t_command_tree *tree);
int						child_process(char **cmd, t_command_tree *tree,
							t_exec *exec, int index);
int						close_fd(int fd, t_command_tree *tree, t_exec *exec);
int						duplicate_pipe(t_command_tree *tree, t_exec *exec,
							int mode);
int						create_pipe(t_exec *exec, t_cmdtree *tree);
int						close_pipe(t_exec *exec);
int						last_child_process(char **cmd, t_command_tree *tree,
							t_exec *exec, int index);

#endif