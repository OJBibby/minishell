/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:44:02 by obibby            #+#    #+#             */
/*   Updated: 2022/10/14 13:41:03 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	check_inbuilt(t_token *token, t_info *info)
{
	int	len;

	len = ft_strlen(token->cmd_args[0]);
	if (!ft_strncmp(token->cmd_args[0], "echo", len))
		return (ft_echo(token, info));
	if (!ft_strncmp(token->cmd_args[0], "cd", len))
		return (ft_cd(token, info));
	if (!ft_strncmp(token->cmd_args[0], "pwd", len))
		return (ft_pwd(token, info));
	if (!ft_strncmp(token->cmd_args[0], "export", len))
		return (ft_export(info));
	if (!ft_strncmp(token->cmd_args[0], "unset", len))
		return (ft_unset(info));
	if (!ft_strncmp(token->cmd_args[0], "env", len))
		return (ft_env(token, info));
	return (-1);
}

int	exec_cmds(t_token *token, t_info *info)
{
	int		inbuilt;

	inbuilt = check_inbuilt(token, info);
	if (inbuilt == 1)
	{
		g_status.exit_status = 2;
		return (1);
	}
	if (inbuilt == 0)
	{
		g_status.exit_status = 0;
		if (info->out_now != -1)
		{
			close(info->out_now);
			info->out_now = -1;
		}
		return (0);
	}
	if (!token->path || token->path && access(token->path, X_OK) == -1)
		return (error_return(0, NULL, "Invalid permissions."));
	return (buff_to_buff(token, info, token->path));
}

int	error_return(int id, void *mem, char *str)
{
	if (id == 1)
		free(mem);
	if (id == 2)
		close(id);
	if (str)
		printf("%s\n", str);
	if (id == 3)
		free(str);
	if (id == 4)
		free_copied_env(mem);
	if (id == 5)
		null_return(mem, 0, NULL, NULL);
	return (1);
}

int	exec_close_fd(t_info *info)
{
	if (info->stdin_fd != -1)
	{
		dup2(info->stdin_fd, STDIN_FILENO);
		close(info->stdin_fd);
		info->stdin_fd = -1;
	}
	if (info->stdout_fd != -1)
	{
		dup2(info->stdout_fd, STDOUT_FILENO);
		close(info->stdout_fd);
		info->stdout_fd = -1;
	}
	if (info->outfile_no != -1)
	{
		close(info->outfile_no);
		info->outfile_no = -1;
	}
	if (info->in_now != -1)
	{
		close(info->in_now);
		info->in_now = -1;
	}
	if (info->out_now != -1)
	{
		close(info->out_now);
		info->out_now = -1;
	}
	return (0);
}

int	exec_free(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	env = NULL;
	return (0);
}

int	execute(t_mini *mini)
{
	t_info	info;

	if (!mini->tokens)
		return (0);
	if (mini->tokens->cmd_args && mini->tokens->cmd_args[0] && !ft_strncmp(mini->tokens->cmd_args[0], "exit", ft_strlen(mini->tokens->cmd_args[0])))
		return (exit_shell(mini));
	init_array(mini, &info);
	while (info.token && info.done_ops < info.total_ops)
	{
		if (init_files(info.token, &info) || !info.token->cmd_args || !info.token->cmd_args[0])
			break ;
		if (exec_cmds(info.token, &info) == 1)
			break ;
		if (g_status.exit_status != 0)
			break ;
		info.token->cmd_args[0];
		info.token = info.token->next;
		info.done_ops++;
	}
	mini->env = info.env_ll;
	exec_close_fd(&info);
	exec_free(info.env);
	return (0);
}
