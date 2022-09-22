#include "../execute/execute.h"

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
			return(1);
		if (delete->prev)
			delete->prev->next = delete->next;
		if (delete->next)
			delete->next->prev = delete->prev;
		if (delete->str)
			free(delete->str);
		free(delete);
	}
	return (2);
}

int	ft_export(t_info *info)
{
	t_env	*env;

	env = get_last_node(info->env_ll);
	if (add_env(info->token, env) == -1)
		return (error_return(0, NULL, "Memory allocation fail."));
	return (2);
}
