/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:21:45 by obibby            #+#    #+#             */
/*   Updated: 2023/02/01 09:36:30 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execute.h"

int	output_env(char **env, int fd)
{
	int	j;
	int	k;

	j = -1;
	while (env[++j])
	{
		write(fd, env[j], ft_strlen(env[j]));
		write(fd, "\n", 1);
	}
	return (0);
}

int	exec_env(t_token *token, t_info *info, char **tmp_env, int i)
{
	int		retval;
	char	**saved_env;

	while (i-- > 0)
		if (shift_args(token))
			return (1);
	saved_env = info->env;
	info->env = tmp_env;
	retval = check_inbuilt(token, info);
	if (retval != -1)
	{
		info->env = saved_env;
		return (retval);
	}
	if (find_exec(token, info))
	{
		info->env = saved_env;
		return (1);
	}
	retval = buff_to_buff(token, info, token->path);
	info->env = saved_env;
	return (retval);
}

int	use_env(t_token *token, t_info *info, int i)
{
	int		fd;
	int		retval;
	char	**tmp_env;

	fd = set_fd(token, info);
	tmp_env = list_to_arr(info->copied_env);
	if (!tmp_env)
		return (error_return(4, info->copied_env, "Memory allocation fail."));
	if (!token->cmd_args[i])
		retval = output_env(tmp_env, fd);
	else
		retval = exec_env(token, info, tmp_env, i);
	if (tmp_env)
		exec_free(tmp_env);
	if (info->copied_env)
		info->copied_env = free_copied_env(info->copied_env);
	return (retval);
}

t_env	*copy_ll(t_env *env)
{
	t_env	*copied_env;
	t_env	*copied_prev;
	t_env	*copied_head;

	copied_prev = NULL;
	copied_head = NULL;
	while (env)
	{
		copied_env = ft_calloc(1, sizeof(t_env));
		if (!copied_env)
			return (free_copied_env(copied_prev));
		if (!copied_head)
			copied_head = copied_env;
		if (copied_prev)
			copied_prev->next = copied_env;
		copied_env->prev = copied_prev;
		copied_prev = copied_env;
		copied_env->str = ft_strdup(env->str);
		if (!copied_env->str)
			return (free_copied_env(copied_prev));
		copied_env->next = NULL;
		env = env->next;
		copied_env = copied_env->next;
	}
	return (copied_head);
}

int	ft_env(t_token *token, t_info *info)
{
	t_env	*env_node;
	int		i;

	i = 0;
	prepare_builtin(token, info);
	if (info->env_ll && !info->copied_env)
		info->copied_env = copy_ll(info->env_ll);
	if (!info->copied_env)
		return (error_return(0, NULL, "Memory allocation fail."));
	while (token->cmd_args[++i])
	{
		if (check_env_input(token->cmd_args[i]))
			return (use_env(token, info, i));
		env_node = find_env_node(info->copied_env, token->cmd_args[i], 1);
		if (!env_node)
		{
			env_node = add_env_node(info, 1);
			if (!env_node)
				return (error_return(0, NULL, "Memory allocation fail."));
		}
		if (add_env_var(token->cmd_args[i], env_node))
			return (1);
	}
	return (use_env(token, info, i));
}
