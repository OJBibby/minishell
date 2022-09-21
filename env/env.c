/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:21:45 by obibby            #+#    #+#             */
/*   Updated: 2022/09/21 11:40:01 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

int	output_env(char **env, t_env *tmp, int fd, int i)
{
	int	j;

	j = -1;
	while (env[++j])
	{
		write(fd, env[j], ft_strlen(env[j]));
		write(fd, "\n", 1);
	}
	free(env);
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

int	ft_env(t_token *token, t_info *info)
{
	int		i;
	int		j;
	t_env	*tmp;

	tmp = get_last_node(info->env_ll);
	i = 0;
	while (token->cmd_args[++i])
	{
		j = -1;
		while (token->cmd_args[i][++j])
		{
			if (token->cmd_args[i][j] == '=')
			{
				tmp->next = malloc(sizeof(t_env));
				tmp->next->prev = tmp;
				tmp = tmp->next;
				tmp->str = ft_strdup(token->cmd_args[i]);
				tmp->next = NULL;
				break ;
			}
		}
		if (!token->cmd_args[i][j])
			break ;
	}
	return (use_env(token, info, tmp, i));
}
