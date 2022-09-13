/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:44:02 by obibby            #+#    #+#             */
/*   Updated: 2022/09/13 22:06:31 by obibby           ###   ########.fr       */
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
	arr = ft_split_or(info->env[i], ':');
	if (!arr)
		return (null_return(NULL, 0, NULL, "Memory allocation fail."));
	i = 0;
	while (arr[i])
	{
		str = ft_strjoin_slash(arr[i++], token->args[0]);
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

	pid = fork();
	if (pid == -1)
		return (error_return(1, path, "Error creating child process."));
	if (pid == 0)
	{
		if (token->output)
		{
			dup2(info->outfile_no, STDOUT_FILENO);
			close(info->outfile_no);
		}
		else
			dup2(info->stdout_fd, STDOUT_FILENO);
		close(info->out_now);
		execve(path, token->args, info->env);
		perror("execve error:");
	}
	else
	{
		if (token->output)
			close(info->outfile_no);
		close(info->out_now);
		waitpid(pid, NULL, 0);
	}
	free(path);
	return (0);
}

int	buff_to_buff(t_token *token, t_info *info, char *path)
{
	int	pid;

	dup2(info->in_now, STDIN_FILENO);
	close(info->in_now);
	if (info->done_ops + 1 == info->total_ops)
		return (final_output(token, info, path));
	close(info->out_now);
	pipe(info->pipe_fd);
	info->in_now = info->pipe_fd[0];
	info->out_now = info->pipe_fd[1];
	pid = fork();
	if (pid == -1)
		return (error_return(1, path, "Error creating child process."));
	if (pid == 0)
	{
		dup2(info->out_now, STDOUT_FILENO);
		close(info->out_now);
		execve(path, token->args, info->env);
		perror("execve error:");
	}
	else
	{
		close(info->out_now);
		waitpid(pid, NULL, 0);
	}
	free(path);
	return (0);
}

int	path_given(t_token *token, char *path)
{
	int	i;

	i = -1;
	if (!access(token->args[0], F_OK))
	{
		path = ft_calloc(ft_strlen(token->args[0]) + 1, sizeof(char));
		if (!path)
			return (1);
		while (token->args[++i])
			path[i] = token->args[0][i];
		return (1);
	}
	return (0);
}

int	check_inbuilt(t_token *token, t_info *info)
{
	int	len;

	len = ft_strlen(token->args[0]);
	if (!ft_strncmp(token->args[0], "echo", len))
		return (ft_echo(token, info));
	if (!ft_strncmp(token->args[0], "cd", len))
		return (ft_cd(token, info));
	if (!ft_strncmp(token->args[0], "pwd", len))
		return (ft_pwd(token, info));
	/*if (!ft_strncmp(token->args[0], "export", len))
		return (my_export(token, info));
	if (!ft_strncmp(token->args[0], "unset", len))
		return (my_unset(token, info));
	if (!ft_strncmp(token->args[0], "env", len))
		return (ft_env(token, info));*/
	return (0);
}

int	exec_cmds(t_token *token, t_info *info)
{
	char	*path;
	int		inbuilt;

	path = NULL;
	inbuilt = check_inbuilt(token, info);
	if (inbuilt == 1)
		return (1);
	if (inbuilt == 2)
		return (0);
	if (!path_given(token, path))
		path = search_path(token, info);
	else if (!path)
		return (error_return(0, NULL, "Memory allocation fail."));
	if (!path)
		return (1);
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

int	out_file(char *file, t_info *info, int append)
{
	if (append)
		info->outfile_no = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		info->outfile_no = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (info->outfile_no == -1)
		return (error_return(0, NULL, "Unable to create output file."));
	return (0);
}

int	in_file(char *file, t_info *info)
{
	char	buf[1];

	info->infile_no = open(file, O_RDONLY);
	if (info->infile_no == -1)
		return (error_return(0, NULL, "Unable to read input file."));
	while (read(info->infile_no, buf, 1))
		write(info->out_now, buf, 1);
	close(info->infile_no);
	return (0);
}

int	init_files(t_token *token, t_info *info)
{
	if (token->input && token->input[0] != '|' && !token->heredoc[0])
	{
		if (in_file(token->input, info))
			return (1);
	}
	if (token->output && token->output[0] != '|')
	{
		if (out_file(token->output, info, token->append[0]))
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

void	init_array(t_token *token, t_info *info)
{
	info->token = token;
	//info->env = mini->env;
	info->total_ops = count_args(token);
	info->done_ops = 0;
	info->stdout_fd = dup(STDOUT_FILENO);
	info->stdin_fd = dup(STDIN_FILENO);
}

int	read_stdin(t_token *token, t_info *info)
{
	char	*ptr;

	ptr = NULL;
	while (ft_strncmp(ptr, token->input, ft_strlen(token->input) + 1))
	{
		if (ptr)
		{
			write(info->out_now, ptr, ft_strlen(ptr));
			write(info->out_now, "\n", 1);
			free(ptr);
		}
		ptr = readline(">");
	}
	free(ptr);
	return (0);
}

int	pipex(t_token *token, char **env)
{
	t_info	info;

	if (!ft_strncmp(token->args[0], "exit", 5))
		return (0); //exit_shell(mini);
	init_array(token, &info);
	info.env = env;
	pipe(info.pipe_fd);
	info.in_now = info.pipe_fd[0];
	info.out_now = info.pipe_fd[1];
	while (info.done_ops < info.total_ops)
	{
		if (info.token->heredoc[0])
			read_stdin(info.token, &info);
		if (init_files(info.token, &info))
			return (1);
		if (exec_cmds(info.token, &info) == 1)
			return (1);
		info.token = info.token->next;
		info.done_ops++;
	}
	return (0);
}

int	main(int argc, char *argv[], char **env)
{
	t_token token;
	t_token	token1;
	int	retval;

	(void)argc;
	(void)argv;
	token.next = &token1;
	token.args = malloc(5 * sizeof(char *));
	token.args[0] = "echo";
	token.args[1] = "this";
	token.args[2] = NULL;
	token.args[3] = NULL;
	token.args[4] = NULL;
	token.input = NULL;
	token.output = "|";
	token.heredoc[0] = 0;
	token.append[0] = 0;
	token1.next = NULL;
	token1.args = malloc(4 * sizeof(char *));
	token1.args[0] = "echo";
	token1.args[1] = "that";
	token1.args[2] = NULL;
	token1.args[3] = NULL;
	token1.input = "|";
	token1.output = NULL;
	token1.heredoc[0] = 0;
	token1.append[0] = 0;
	retval = pipex(&token, env);
	free(token.args);
	free(token1.args);
	return (retval);
}
