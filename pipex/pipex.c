/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:44:02 by obibby            #+#    #+#             */
/*   Updated: 2022/08/23 09:57:42 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*null_return(char **arr, int id, void *ptr, char *str)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	error_return(id, ptr, str);
	return (NULL);
}

void	free_joined(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*search_path(t_token *token, t_info *info)
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
	/*if (ft_strncmp(str, ptr->str, 5))
	{
		while (ptr->next)
		{
			ptr = info->env->next;
			if (ft_strncmp(str, ptr->str, 5) == 0)
				break ;
		}
	}*/
	arr = ft_split_or(info->env[i], ':');
	if (!arr)
		return (null_return(NULL, 0, NULL, "Memory allocation fail."));
	i = 0;
	while (arr[i])
	{
		str = ft_strjoin_slash(arr[i++], info->token->cmd_args[0]);
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
}

void	free_arr(t_cmd *cmds, void *ptr)
{
	while (cmds->total-- > 0)
		free(cmds->cmds[cmds->total]);
	free(cmds->prog);
	free(ptr);
}

int	final_output(t_token *token, t_info *info, char *path)
{
	int	pid;
	
	close(info->out_now);
	if (info->outfile)
		info->out_now = info->outfile_no;
	else
		dup2(info->stdout_fd, STDOUT_FILENO);
	pid = fork();
	if (pid == -1)
		return (error_return(1, path, "Error creating child process."));
	if (pid == 0)
		execve(path, token->cmd_args, info->env);
	else
	{
		close(info->in_now);
		dup2(info->stdin_fd, STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
	return (0);
}

int	buff_to_buff(t_token *token, t_info *info, char *path)
{
	int	pid;
	
	if (info->done_ops + 1 == info->total_ops)
		return (final_output(token, info, path));
	pid = fork();
	if (pid == -1)
		return (error_return(1, path, "Error creating child process."));
	if (pid == 0)
	{
		close(info->in_now);
		dup2(info->out_now, STDOUT_FILENO);
		close(info->out_now);
		execve(path, token->cmd_args, info->env);
	}
	else
	{
		close(info->out_now);
		if (info->done_ops == 0)
		{
			close(info->in_now);
			info->in_now = info->pipe_fd[0];
		}
		dup2(info->in_now, STDIN_FILENO);
		close(info->in_now);
		waitpid(pid, NULL, 0);
	}
	return (0);
}

int	exec_cmds(t_token *token, t_info *info)
{
	char	*path;

	path = search_path(token, info);
	if (!path)
		return (1);
	//printf("path: %s\n", path);										//path to prog
	//printf("%s, %s, %s\n", token->cmd_args[0], token->cmd_args[1], token->cmd_args[2]); //prog + flags
	if (access(path, X_OK) == -1)
		return (error_return(1, path, "Invalid permissions."));
	return (buff_to_buff(token, info, path));
}

int	error_return(int id, void *mem, char *str)
{
	if (id == 1)
		free(mem);
	if (id == 2)
		close(id);
	printf("%s\n", str);
	return(1);
}

int	out_file(char *file, t_info *info)
{
	int	i;

	i = 0;
	info->outfile_no = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (info->outfile_no == -1)
		return (error_return(0, NULL, "Unable to create output file."));
	while (file[i])
		i++;
	info->outfile = ft_calloc(i + 1, sizeof(char));
	if (!info->outfile)
		return (error_return(2, &info->outfile_no, "Memory allocation fail."));
	i = -1;
	while (file[++i])
		info->outfile[i] = file[i];
	return (0);
}

int	in_file(char *file, t_info *info)
{
	int	i;
	
	i = 0;
	info->infile_no = open(file, O_RDONLY);
	if (info->infile_no == -1)
		return (error_return(0, NULL, "Unable to read input file."));
	while (file[i])
		i++;
	info->infile = ft_calloc(i + 1, sizeof(char));
	if (!info->infile)
		return (error_return(2, &info->infile_no, "Memory allocation fail."));
	i = -1;
	while (file[++i])
		info->infile[i] = file[i];
	return (0);
}

int	init_files(t_token *args, t_info *info)
{
	if (args->infile && in_file(args->infile, info))
		return (1);
	if (args->outfile && out_file(args->outfile, info))
	{
		if (args->infile)
			close(info->infile_no);
		return (1);
	}
	return (0);
}

int	count_args(t_token *token)
{
	int	i;
	t_token	*ptr;

	ptr = token;
	i = 0;
	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

void	init_array(t_mini *mini, t_info *info)
{
	info->token = mini->tokens;
	//info->env = mini->env;
	info->total_ops = count_args(mini->tokens);
	info->done_ops = 0;
	info->token->infile = NULL;
	info->token->outfile = NULL;
	info->stdout_fd = dup(STDOUT_FILENO);
	info->stdin_fd = dup(STDIN_FILENO);
}

int	pipex(t_mini *mini, char **env)
{
	t_info	info;

	init_array(mini, &info);
	info.env = env;
	if (info.token->infile || info.token->outfile)
		if (init_files(info.token, &info))
			return (1);
	while (info.done_ops < info.total_ops)
	{
		pipe(info.pipe_fd);
		info.out_now = info.pipe_fd[1];
		if (info.done_ops == 1 || !info.infile)
			info.in_now = info.pipe_fd[0];
		if (exec_cmds(info.token, &info) == 1)
			return (1);
		info.token = info.token->next;
		info.done_ops++;
	}
	//free(info.infile);
	//free(info.outfile);
	return (0);
}
