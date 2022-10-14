/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:11:02 by obibby            #+#    #+#             */
/*   Updated: 2022/10/14 15:56:26 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	exec_close_builtin(t_info *info)
{
	if (info->out_now != -1)
	{
		close(info->out_now);
		info->out_now = -1;
	}
	if (info->in_now != -1)
	{
		close(info->in_now);
		info->in_now = -1;
	}
}

void	exec_close_fd2(t_info *info)
{
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
	if (info->input_in != -1)
	{
		close(info->input_in);
		info->input_in = -1;
	}
	if (info->input_out != -1)
	{
		close(info->input_out);
		info->input_out = -1;
	}
}

void	exec_close_fd(t_info *info)
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
	exec_close_fd2(info);
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
