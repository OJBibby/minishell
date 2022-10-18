/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:39:52 by obibby            #+#    #+#             */
/*   Updated: 2022/10/14 17:20:17 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	output_child(t_token *token, t_info *info, char *path)
{
	int	retval;

	if (token->output && token->output[0][0] != '|')
	{
		dup2(info->outfile_no, STDOUT_FILENO);
		close(info->outfile_no);
	}
	else if (token->output)
	{
		dup2(info->out_now, STDOUT_FILENO);
		close(info->out_now);
	}
	else
	{
		dup2(info->stdout_fd, STDOUT_FILENO);
		close(info->stdout_fd);
	}
	retval = execve(token->path, token->cmd_args, info->env);
	perror("");
	exit(retval);
}

int	final_output(t_token *token, t_info *info, char *path)
{
	int	status;

	g_status.pid = fork();
	if (g_status.pid == -1)
		return (error_return(1, path, "Error creating child process."));
	if (g_status.pid == 0)
		output_child(token, info, path);
	else
	{
		exec_close_fd(info, 1);
		waitpid(g_status.pid, &status, 0);
		g_status.pid = 0;
		if (WIFEXITED(status))
			g_status.exit_status = WEXITSTATUS(status);
	}
	return (0);
}

void	prepare_output(t_token *token, t_info *info)
{
	if (token->input)
	{
		if (info->input_in != -1)
		{
			dup2(info->input_in, STDIN_FILENO);
			close(info->input_in);
			close(info->input_out);
			info->input_out = -1;
			info->input_in = -1;
			exec_close_builtin(info);
		}
		else
		{
			dup2(info->in_now, STDIN_FILENO);
			close(info->in_now);
			info->in_now = -1;
		}
	}
	else
		exec_close_builtin(info);
}

int	buff_to_buff(t_token *token, t_info *info, char *path)
{
	int	status;

	prepare_output(token, info);
	if (info->done_ops + 1 == info->total_ops)
		return (final_output(token, info, path));
	pipe(info->pipe_fd);
	info->in_now = info->pipe_fd[0];
	info->out_now = info->pipe_fd[1];
	g_status.pid = fork();
	if (g_status.pid == -1)
		return (error_return(1, path, "Error creating child process."));
	if (g_status.pid == 0)
		output_child(token, info, path);
	else
	{
		exec_close_fd(info, 0);
		waitpid(g_status.pid, &status, 0);
		g_status.pid = 0;
		if (WIFEXITED(status))
			g_status.exit_status = WEXITSTATUS(status);
	}
	return (0);
}
