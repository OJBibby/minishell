/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:44:02 by obibby            #+#    #+#             */
/*   Updated: 2022/10/04 21:46:03 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*char	*null_return(char **arr, int id, void *ptr, char *str)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	error_return(id, ptr, str);
	return (NULL);
}*/

/*void	free_joined(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}*/

/*char	*search_path(t_token *token, t_info *info)
{
	int		i;
	char	*str;
	char	**arr;

	str = "PATH=";
	i = 0;
	while (info->env[i])
	{
		if (ft_strncmp(str, info->env[i], 5) == 0)
			break ;
		i++;
	}
	arr = ft_split_or(info->env[i], ':');
	if (!arr)
		return (null_return(NULL, 0, NULL, "Memory allocation fail."));
	i = 0;
	while (arr[i])
	{
		str = ft_strjoin_slash(arr[i++], token->cmd_args[0]);
		if (!str)
		{
			free_joined(arr);
			return (null_return(arr, 0, NULL, "Memory allocation fail."));
		}
		if (access(str, F_OK) == 0)
			break ;
		free(str);
		if (!arr[i])
			return (null_return(arr, 1, str, "Command not found."));
	}
	free_joined(arr);
	return (str);
}*/

/*void	free_arr(t_cmd *cmds, void *ptr)
{
	while (cmds->total-- > 0)
		free(cmds->cmds[cmds->total]);
	free(cmds->prog);
	free(ptr);
}*/

/*int	path_given(t_token *token, char *path)
{
	int	i;

	i = -1;
	if (!access(token->cmd_args[0], F_OK))
	{
		path = ft_calloc(ft_strlen(token->cmd_args[0]) + 1, sizeof(char));
		if (!path)
			return (1);
		while (token->cmd_args[0][++i])
			path[i] = token->cmd_args[0][i];
		return (1);
	}
	return (0);
}*/

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
	return (0);
}

int	exec_cmds(t_token *token, t_info *info)
{
	int		inbuilt;

	inbuilt = check_inbuilt(token, info);
	if (inbuilt == 1)
	{
		g_exit = 2;
		return (1);
	}
	if (inbuilt == 2)
	{
		g_exit = 0;
		return (0);
	}
	if (access(token->path, X_OK) == -1)
		return (error_return(0, NULL, "Invalid permissions."));
	return (buff_to_buff(token, info, token->path));
}

int	error_return(int id, void *mem, char *str)
{
	if (id == 1)
		free(mem);
	if (id == 2)
		close(id);
	if (id == 3)
		free(str);
	printf("%s\n", str);
	return (1);
}

int	execute(t_mini *mini)
{
	t_info	info;

	if (!mini->tokens)
		return (0);
	if (!mini->tokens->cmd_args)
		return (0);
	if (!ft_strncmp(mini->tokens->cmd_args[0], "exit", ft_strlen(mini->tokens->cmd_args[0])))
		exit_shell(mini);
	init_array(mini, &info);
	while (info.token && info.done_ops < info.total_ops)
	{
		if (init_files(info.token, &info))
			break ;
		if (exec_cmds(info.token, &info) == 1)
			break ;
		if (g_exit != 0)
			break ;
		info.token = info.token->next;
		info.done_ops++;
	}
	if (info.stdin_fd)
	{
		dup2(info.stdin_fd, STDIN_FILENO);
		close(info.stdin_fd);
	}
	if (info.stdout_fd)
	{
		dup2(info.stdout_fd, STDOUT_FILENO);
		close(info.stdout_fd);
	}
	return (0);
}
