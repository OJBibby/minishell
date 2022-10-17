/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:44:02 by obibby            #+#    #+#             */
/*   Updated: 2022/10/17 15:09:43 by obibby           ###   ########.fr       */
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

int	check_exit(t_mini *mini)
{
	int	len;

	if (!mini->tokens->cmd_args)
		return (0);
	if (!mini->tokens->cmd_args[0])
		return (0);
	len = ft_strlen(mini->tokens->cmd_args[0]);
	if (!ft_strncmp(mini->tokens->cmd_args[0], "exit", len))
		return (exit_shell(mini));
	return (0);
}

int	execute(t_mini *mini)
{
	t_info	info;

	if (!mini->tokens)
		return (0);
	if (check_exit(mini))
		return (1);
	init_array(mini, &info);
	while (info.token && info.done_ops < info.total_ops)
	{
		if (init_files(info.token, &info) || !info.token->cmd_args
			|| !info.token->cmd_args[0])
			break ;
		if (exec_cmds(info.token, &info) == 1)
			break ;
		if (g_status.exit_status != 0)
			break ;
		info.token = info.token->next;
		info.done_ops++;
	}
	mini->env = info.env_ll;
	exec_close_fd(&info, 1);
	exec_free(info.env);
	return (0);
}
