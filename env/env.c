/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:21:45 by obibby            #+#    #+#             */
/*   Updated: 2022/10/13 16:48:30 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

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
			return (error_return(1, tmp_env, "Memory allocation fail."));
	saved_env = info->env;
	info->env = tmp_env;
	if (!access(token->cmd_args[0], F_OK))
		token->path = token->cmd_args[0];
	else
		token->path = search_path(token, info);
	if (!token->path)
	{
		info->env = saved_env;
		return (1);
	}
	retval = exec_cmds(token, info);
	info->env = saved_env;
	return (retval);
}

int	use_env(t_token *token, t_info *info, t_env *tmp, int i)
{
	int		fd;
	int		retval;
	char	**tmp_env;
	char	**saved_env;

	fd = set_fd(token, info);
	tmp_env = list_to_arr(info->env_ll);
	if (!tmp_env)
		return (error_return(0, NULL, "Memory allocation fail."));
	if (!token->cmd_args[i])
		retval = output_env(tmp_env, fd);
	else
		retval = exec_env(token, info, tmp_env, i);
	revert_list(tmp, i);
	exec_free(tmp_env);
	return (retval);
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
	int		i;
	int		j;

	i = 0;
	while (token->cmd_args[++i])
	{
		j = 0;
		while (token->cmd_args[i][j])
		{
			if (token->cmd_args[i][j] == '=')
				break ;
			j++;
			if (!token->cmd_args[i][j])
				return (use_env(token, info, env, i));
		}
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
