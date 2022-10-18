/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:42:19 by obibby            #+#    #+#             */
/*   Updated: 2022/10/17 15:09:39 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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
	char		buf[1];
	struct stat	stats;

	info->infile_no = open(file, O_RDONLY);
	if (info->infile_no == -1)
		return (error_return(0, NULL, "Unable to read input file."));
	fstat(info->infile_no, &stats);
	if (S_ISDIR(stats.st_mode))
		return (error_return(3, NULL, ft_strjoin(file, ": is a directory.")));
	while (read(info->infile_no, buf, 1))
		write(info->input_out, buf, 1);
	close(info->infile_no);
	return (0);
}

int	read_stdin(t_token *token, t_info *info, int i)
{
	char	*ptr;

	ptr = NULL;
	while (ft_strncmp(ptr, token->input[i], ft_strlen(token->input[i])))
	{
		if (ptr)
		{
			ptr = env_var(ptr, info->env);
			write(info->input_out, ptr, ft_strlen(ptr));
			write(info->input_out, "\n", 1);
			free(ptr);
		}
		ptr = readline(">");
	}
	free(ptr);
	return (0);
}

int	output_init(t_token *token, t_info *info)
{
	int	i;

	i = 0;
	while (token->output[i])
	{
		if (token->output[i][0] != '|')
		{
			if (out_file(token->output[i], info, token->append[i]))
				return (1);
		}
		else
		{
			if (info->out_now == -1 && info->in_now == -1)
			{
				pipe(info->pipe_fd);
				info->out_now = info->pipe_fd[1];
				info->in_now = info->pipe_fd[0];
			}
		}
		if (token->output[++i] && token->output[i][0] != '|')
			close(info->outfile_no);
	}
	return (0);
}

int	input_init(t_token *token, t_info *info)
{
	int	i;

	i = 0;
	while (token->input[i])
	{
		pipe(info->input_pipe);
		info->input_in = info->input_pipe[0];
		info->input_out = info->input_pipe[1];
		if (token->heredoc && token->heredoc[i])
			read_stdin(token, info, i);
		else if (token->input[i][0] != '|')
		{
			if (in_file(token->input[i], info))
				return (1);
		}
		if (token->input[++i] && info->input_in != -1 && info->input_out != -1)
		{
			close(info->input_in);
			close(info->input_out);
			info->input_in = -1;
			info->input_out = -1;
		}
	}
	return (0);
}
