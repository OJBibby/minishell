/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:21:45 by obibby            #+#    #+#             */
/*   Updated: 2022/09/22 18:48:32 by obibby           ###   ########.fr       */
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
	free(env);
	revert_list(tmp, i);
	return (2);
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
		if (shift_args(token->cmd_args))
			return (error_return(1, tmp_env, "Memory allocation fail."));
		saved_env = info->env;
		info->env = tmp_env;
		retval = exec_cmds(token, info);
		info->env = saved_env;
		free(tmp_env);
		revert_list(tmp, i);
	}
	/*if (info->stdout_fd == -1)
		info->stdout_fd = dup(STDOUT_FILENO);*/
	return (retval);
}

int	add_env(t_token *token, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	while (token->cmd_args[++i])
	{
		j = -1;
		while (token->cmd_args[i][++j])
		{
			if (token->cmd_args[i][j] == '=')
			{
				env->next = ft_calloc(1, sizeof(t_env));
				if (!env->next)
					return (-1);
				env->next->prev = env;
				env = env->next;
				env->str = ft_strdup(token->cmd_args[i]);
				env->next = NULL;
				break ;
			}
		}
		if (!token->cmd_args[i][j])
			break ;
	}
	return (i);
}

int	ft_env(t_token *token, t_info *info)
{
	t_env	*tmp;
	int i;

	tmp = get_last_node(info->env_ll);
	i = add_env(token, tmp);
	if (i == -1)
		return (error_return(0, NULL, "Memory allocation fail."));
	return (use_env(token, info, tmp, i));
}
