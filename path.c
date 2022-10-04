#include "minishell.h"

int	check_builtin(char **args)
{
	int	i;

	if (!args[0])
		return(-1);
	if (!ft_strncmp_p(args[0], "export", 6))
		return(1);
	else if (!ft_strncmp_p(args[0], "unset", 5))
		return(1);
	else if (!ft_strncmp_p(args[0], "echo", 4))
		return(1);
	else if (!ft_strncmp_p(args[0], "cd", 2))
		return(1);
	else if (!ft_strncmp_p(args[0], "pwd", 3))
		return(1);
	else if (!ft_strncmp_p(args[0], "env", 3))
		return(1);
	else if (!ft_strncmp_p(args[0], "exit", 4))
		return(1);
	return (0);
}