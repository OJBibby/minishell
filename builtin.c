#include "pipex/pipex.h"

int	my_unset(t_info *info)
{
	t_token	*token;
	t_env	*delete;
	t_env	*env;

	token = info->token;
	env = info->env_ll;
	delete = get_env_node(env, token->cmd_args[1]);
	if (!delete)
		return(-1);
	delete->prev->next = delete->next;
	delete->next->prev = delete->prev;
	if (delete->str)
		free(delete->str);
	free(delete);
	return (0);
}

int	my_export(t_info *info)
{
	t_token	*token;
	t_env	*exp;
	t_env	*env;
	//char	*tmp;

	token = info->token;
	env = info->env_ll;
	//exp = get_env_str(env, token->cmd_args[1]);
	while(env->next)
		env = env->next;
	exp = malloc(sizeof(t_env));
	exp->next = NULL;
	exp->prev = env;
	exp->str = ft_strdup(token->cmd_args[1]);
	env->next = exp;
	//tmp = exp;
	//exp = ft_strdup(token->cmd_args[1]);
	//if (tmp)
	//	free(tmp);
	return (0);
}