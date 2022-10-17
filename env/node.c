/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:01:23 by obibby            #+#    #+#             */
/*   Updated: 2022/10/15 22:38:59 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

t_env	*find_env_node(t_env *env, char *str, int mode)
{
	t_env	*tmp;
	t_env	*prev;
	int		len;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->str, str, i + mode))
			if (mode == 1 || (mode == 0 && !str[i] && tmp->str[i] == '='))
				return (tmp);
		prev = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

t_env	*add_env_node(t_info *info, int temp)
{
	t_env	*env;
	t_env	*prev;

	if (temp)
		env = info->copied_env;
	else
		env = info->env_ll;
	while (env)
	{
		prev = env;
		env = env->next;
	}
	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	env->prev = prev;
	prev->next = env;
	env->str = NULL;
	env->next = NULL;
	return (env);
}

int	find_exec(t_token *token, t_info *info)
{
	if (!access(token->cmd_args[0], F_OK))
		token->path = token->cmd_args[0];
	else
		token->path = search_path(token, info);
	if (!token->path)
		return (1);
	if (access(token->path, X_OK) == -1)
		return (error_return(0, NULL, "Invalid permissions."));
	return (0);
}
