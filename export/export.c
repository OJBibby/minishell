#include "../execute/execute.h"

int	print_exported(t_env *env, int fd)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		write(fd, "declare -x ", 11);
		write(fd, temp->str, ft_strlen(temp->str));
		write(fd, "\n", 1);
		temp = temp->next;
	}
	return (0);
}

int	ft_unset(t_info *info)
{
	t_token	*token;
	t_env	*delete;
	t_env	*env;
	int		i;

	token = info->token;
	i = 0;
	while (token->cmd_args[++i])
	{
		delete = get_env_node(info->env_ll, token->cmd_args[i]);
		if (!delete)
			return (1);
		if (delete->prev)
			delete->prev->next = delete->next;
		if (delete->next)
			delete->next->prev = delete->prev;
		if (delete->str)
			free(delete->str);
		free(delete);
	}
	return (0);
}

int	ft_export(t_info *info)
{
	t_env	*env;
	int		fd;
	int		i;
	int		j;

	fd = set_fd(info->token, info);
	if (!info->token->cmd_args[1])
		return (print_exported(info->env_ll, fd));
	i = 0;
	while (info->token->cmd_args[++i])
	{
		j = 0;
		while (info->token->cmd_args[i][j] && info->token->cmd_args[i][j] != '=')
			j++;
		if (!info->token->cmd_args[i][j])
			continue ;
		env = find_env_node(info->env_ll, info->token->cmd_args[i], j);
		if (!env)
			return (error_return(0, NULL, "Memory allocation fail."));
		if (add_env(info->token->cmd_args[i], env) == -1)
			return (error_return(0, NULL, "Memory allocation fail."));
	}
	return (0);
}
