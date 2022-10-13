/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:21:45 by obibby            #+#    #+#             */
/*   Updated: 2022/10/13 11:37:00 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

int	output_env(char **env, t_env *tmp, int fd, int i)
{
	int	j;
	int	k;

	j = -1;
	while (env[++j])
	{
		write(fd, env[j], ft_strlen(env[j]));
		write(fd, "\n", 1);
	}
	revert_list(tmp, i);
	return (0);
}

int	use_env(t_token *token, t_info *info, t_env *tmp, int i)
{
	int		j;
	int		fd;
	int		retval;
	char	**tmp_env;
	char	**saved_env;

	fd = set_fd(token, info);
	tmp_env = list_to_arr(info->env_ll);
	if (!tmp_env)
		return (error_return(0, NULL, "Memory allocation fail."));
	if (!token->cmd_args[i])
		retval = output_env(tmp_env, tmp, fd, i);
	else
	{
		j = i;
		while (j-- > 0)
			if (shift_args(token->cmd_args))
				return (error_return(1, tmp_env, "Memory allocation fail."));
		saved_env = info->env;
		info->env = tmp_env;
		retval = exec_cmds(token, info);
		info->env = saved_env;
		revert_list(tmp, i);
	}
	exec_free(tmp_env);
	return (retval);
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

int	add_env_var(char *var, t_env *env)
{
	int	i;
	int	j;

	if (env->str)
		return (replace_var(var, env));
	i = -1;
	while (var[++i])
	{
		if (var[i] == '=' && var[i + 1])
		{
			env->str = ft_strdup(var);
			if (!env->str)
				return (error_return(1, env, "Memory allocation fail."));
			break ;
		}
	}
	return (0);
}

int	ft_env(t_token *token, t_info *info)
{
	t_env	*env;
	int 	i;
	int		j;

	i = 0;
	while (token->cmd_args[++i])
	{
		if (!token->cmd_args[i])
			return (use_env(token, info, env, i));
		env = find_env_node(info->env_ll, token->cmd_args[i], 1);
		if (!env)
		{
			env = add_env_node(info);
			if (!env)
				return (error_return(0, NULL, "Memory allocation fail."));
		}
		if (add_env_var(token->cmd_args[i], env))
			return (1);
	}
	return (use_env(token, info, env, i));
}
