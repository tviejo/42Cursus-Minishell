# include "../includes/minishell.h"

int g_signal;

bool wait_one_process()
{
    int status;

    status = 0;
    waitpid(-1, &status, 0);
    if (WIFEXITED(status))
    {
        g_signal = WEXITSTATUS(status);
        return (true);
    }
    else if (WIFSIGNALED(status))
    {
        g_signal = 128 + WTERMSIG(status);
        return (false);
    }
    return (true);
}

void wait_all_process()
{
    int i;
    int status;

    status = 0;
    i = 0;
    while (waitpid(-1, &status, 0) > 0)
    {
       if (WIFEXITED(status))
            g_signal = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            g_signal = 128 + WTERMSIG(status);
    }
}
