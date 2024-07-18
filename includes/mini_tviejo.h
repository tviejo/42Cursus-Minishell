#ifndef MINI_TVIEJO_H
# define MINI_TVIEJO_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <dirent.h>

enum e_builtin
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
}	t_exec;

int		store_env(t_exec *exec, char **env);
char	*find_path(char *name, t_exec *exec);
int		update_oldpwm(t_exec *exec);
int		print_env(t_exec *exec);
int		update_pwd(t_exec *exec, char *pwd);

#endif