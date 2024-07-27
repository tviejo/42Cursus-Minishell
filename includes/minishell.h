/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sarr <ade-sarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:17:18 by tviejo            #+#    #+#             */
/*   Updated: 2024/07/27 04:04:37 by ade-sarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Etapes du Parsing
 * =================
 * Objectif: ligne de commande (string) -> arbre binaire AST (t_cmdtree):
 * la ligne de commande saisie par l'utilisateur sera transformée en une
 * répresentation syntaxique abstraite sous forme d'un arbre binaire (AST).
 *
 * I.   Traitement des guillements simples et double, substitution des variables
 * d'environnement et des wildcards, identification des opérateurs et des
 * commandes ainsi que leurs options et arguments.
 * II.  Construction d'une pile NPI (notation polonaise inversée) des opérations
 * et commandes à executer.
 * III. Construction de l'arbre binaire AST en dépilant tous les éléments de la
 * pile NPI. Chaque noeud (t_cmdtree) représente soit une commande
 * (type = nt_command ou nt_piped_cmd), soit une "opération" :
 *   - une redirection ('<', '<<', '>', '>>', argument[0] = "nom de fichier
 * ou delimiter"),
 *   - un pipe '|' (type = nt_pipe, argument = NULL),
 *   - un OU logique '||' (type = nt_OR, argument = NULL),
 *   - un ET logique '&&' (type = nt_AND, argument = NULL).
 *
 * Une commande est toujours une feuille (left = NULL et right = NULL).
 * Un redirection n'a qu'une descendance à droite (left = NULL).
 * Dans les autres cas ('|', '||', '&&'), il y a une descendance des deux cotés.
 * node.nb_command est le nombre de commandes portées par le noeud et sa
 * descendance (left + right).
 * Si une commande se trouve dans la descendance gauche d'au moins un pipe son
 * type est nt_piped_cmd (sinon nt_command).
 */

# include "mini_ade_sarr.h"
# include "mini_tviejo.h"

extern int				g_signal;

enum					e_side
{
	e_left,
	e_right
};

/* nt_piped_cmd est utilisé pour indiquer que la sortie de la commande sera
 * redirigée vers l'entrée de la commande suivante (elle même de type
 * nt_piped_cmd ou nt_command si dernière commande de son groupe).
 */

enum					e_nodetype
{
	nt_command,
	nt_piped_cmd,
	nt_infile,
	nt_here_doc,
	nt_out_truncate,
	nt_out_append,
	nt_pipe,
	nt_OR,
	nt_AND,
	nt_open_parenth,
	nt_close_parenth,
	nt_number_of_nodetype,
	nt_exec_done
};

typedef struct s_data
{
	int					error_code;
	bool				end_exec;
	char				**env;
	int					env_len;
	int					infile;
	int					outfile;
	int					dupstdin;
	int					dupstdout;
	int					fdpipe[2];
	int					oldtype;
	int					side;
	pid_t				*pid;
	char				**separators;
	t_operator			*operators;
	t_stack				*pile_ope;
	t_stack				*pile_npi;
	t_queue				*file_lex;
	struct s_cmdtree	*cmdtree;
	char				**splited_words;
	int					debug_mode;
}						t_data;

typedef struct s_cmdtree
{
	enum e_nodetype		type;
	char				**argument;
	int					nb_command;
	struct s_cmdtree	*left;
	struct s_cmdtree	*right;
}						t_command_tree;

typedef t_command_tree	t_cmdtree;

/*				EXEC				*/

int						ft_export(t_command_tree *tree, t_data *exec);
int						ft_cd(t_command_tree *tree, t_data *exec);
int						ft_env(t_data *exec, t_command_tree *tree);
int						ft_pwd(t_data *exec);
int						ft_unset(t_command_tree *tree, t_data *exec);
int						ft_echo(t_command_tree *tree);
int						find_builtin(t_command_tree *tree);
int						exec_builtin(t_command_tree *tree, t_data *exec);
int						ft_exit(t_command_tree *tree, t_data *exec);
char					*find_path_cmd(char **envp);
int						ft_close_error(t_command_tree *tree, t_data *exec);
void					exec_cmd(t_command_tree *tree, t_data *exec);
int						cmd_process_and_or(t_command_tree *tree, t_data *exec);
int						calloc_pid(t_data *exec, t_command_tree *tree);
int						child_process(t_command_tree *tree, t_data *exec);
int						close_fd(int fd, t_command_tree *tree, t_data *exec);
int						duplicate_pipe(t_command_tree *tree, t_data *exec,
							int mode);
int						create_pipe(t_data *exec, t_cmdtree *tree);
int						close_pipe(t_data *exec);
int						last_child_process(t_command_tree *tree, t_data *exec);
int						create_fork(t_command_tree *tree, t_data *exec);
int						redir_infile(t_command_tree *tree, t_data *exec);
int						redir_outfile(t_command_tree *tree, t_data *exec);
int						here_doc(t_command_tree *tree, t_data *exec);
bool					is_and_or(t_command_tree *tree);
int						exec_cmdtree(t_command_tree *tree, t_data *exec);
int						store_env(t_data *exec, char **env);
char					*find_path(char *name, t_data *exec);
int						free_env(t_data *exec);
int						update_oldpwm(t_data *exec);
int						print_env(t_data *exec);
int						update_pwd(t_data *exec, char *pwd);
char					**expand_env(t_data *exec);
char					*find_cmd(char **cmd, char **paths);
int						ft_free_pid(t_data *exec);
void					wait_all_process(t_data *exec);
bool					wait_one_process(t_data *exec, int index);
void					signal_handler(int sig);
void					signal_handler_here_doc(int sig);
int						dup_std(t_data *exec);
int						close_std_fd(t_data *exec);
char					**expand_env(t_data *exec);
char					**add_back_env(t_data *exec, char *env_var);
int						exec_node_left(t_cmdtree *tree, t_data *exec);
int						exec_node_right(t_cmdtree *tree, t_data *exec);
bool					is_node(t_cmdtree *tree);
bool					is_redir(t_cmdtree *tree);
void					ft_redir(t_command_tree *tree, t_data *exec);
void					signal_init(void);
void					signal_handler_process(void);
void					signal_handler_here_doc(int sig);
void					signal_handler(int sig);
void					signal_sigint(int sig);
void					signal_sigquit(int sig);
void					init_exec(t_data *mshell);
void					close_exec(t_data *mshell);
char					*find_wildcard(char *wildcard);

/*				PARSING					*/

char					*lexer(t_data *ms, char *cmdline);

bool					init_parsing(t_data *ms);
void					free_parsing(t_data *ms);
t_cmdtree				*parse_cmdline(t_data *ms, char *cmdline);
void					print_cmdtree(t_data *ms);
void					free_cmdtree(t_data *ms);
t_cmdtree				*new_node(t_data *ms, char ***words);
void					print_stack_node(t_cmdtree *cmdtree, t_operator *ope);
int						get_node_priority(t_data *ms, t_cmdtree *node);
enum e_nodetype			get_node_type(t_data *ms, char *word);
int						get_nb_args(t_data *ms, char **words);
void					if_debug_print_npi_stack(t_data *ms);

char					*get_env_var(t_data *ms, char *varname);

int						print_minishell(void);

#endif