/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:34:31 by obibby            #+#    #+#             */
/*   Updated: 2022/10/13 17:06:52 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

int	revert_list(t_env *tmp, int i)
{
	while (--i > 0)
	{
		free(tmp->str);
		tmp = tmp->prev;
		free(tmp->next);
		tmp->next = NULL;
	}
	return (0);
}

int	shift_args(t_token *token)
{
	int		i;
	int		j;
	char	**args;
	char	**new_args;

	args = token->cmd_args;
	i = 1;
	while (args[i])
		i++;
	new_args = ft_calloc(i, sizeof(char **));
	if (!new_args)
		return (1);
	i = 0;
	free(args[i]);
	while (args[++i])
	{
		new_args[i - 1] = ft_calloc(ft_strlen(args[i]) + 1, sizeof(char *));
		if (!new_args[i - 1])
			return (1);
		j = -1;
		while (args[i][++j])
			new_args[i - 1][j] = args[i][j];
		new_args[i - 1][j] = 0;
		free(args[i]);
	}
	free(args[i]);
	free(args);
	new_args[i - 1] = NULL;
	token->cmd_args = new_args;
	return (0);
}

t_env	*add_env_node(t_info *info)
{
	t_env	*env;
	t_env	*prev;

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

int	replace_var(char *var, t_env *env)
{
	free(env->str);
	env->str = NULL;
	env->str = ft_strdup(var);
	if (!env->str)
	{
		if (env->next && env->prev)
		{
			env->prev->next = env->next;
			env->next->prev = env->prev;
		}
		else if (env->next)
			env->next->prev = NULL;
		else if (env->prev)
			env->prev->next = NULL;
		return (error_return(1, env, "Memory allocation fail."));
	}
	return (0);
}

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
