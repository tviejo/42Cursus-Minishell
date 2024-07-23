#ifndef MINI_TVIEJO_H
# define MINI_TVIEJO_H

# include "../libft/libft.h"
# include "minishell.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

enum		e_builtin
{
	b_not_builtin,
	b_cd,
	b_echo,
	b_env,
	b_exit,
	b_pwd,
	b_unset,
	b_export
};

typedef struct exec
{
	char	**env;
	int		env_len;
	int		infile;
	int		outfile;
	int		fdpipe[2];
	int 	oldtype;
	int		side;
	pid_t	*pid;
}			t_exec;

int			store_env(t_exec *exec, char **env);
char		*find_path(char *name, t_exec *exec);
int			free_env(t_exec *exec);
int			update_oldpwm(t_exec *exec);
int			print_env(t_exec *exec);
int			update_pwd(t_exec *exec, char *pwd);
char		**expand_env(t_exec *exec);
char		*find_cmd(char **cmd, char **paths);
int			ft_free_pid(t_exec *exec);
void		wait_all_process(void);
bool		wait_one_process(void);
void		signal_handler(int sig);
void		signal_handler_here_doc(int sig);
void		signal_handler_process(int sig);

#endif