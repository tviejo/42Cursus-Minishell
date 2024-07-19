#ifndef MINI_TVIEJO_H
# define MINI_TVIEJO_H

# include "../libft/libft.h"
# include "minishell.h"
# include <dirent.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>


extern int status;

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
	pid_t 	*pid;
}			t_exec;

int			store_env(t_exec *exec, char **env);
char		*find_path(char *name, t_exec *exec);
int			free_env(t_exec *exec);
int			update_oldpwm(t_exec *exec);
int			print_env(t_exec *exec);
int			update_pwd(t_exec *exec, char *pwd);
char		**expand_env(t_exec *exec);


#endif