/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:42:19 by obibby            #+#    #+#             */
/*   Updated: 2022/09/21 09:43:29 by obibby           ###   ########.fr       */
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
	char	buf[1];

	info->infile_no = open(file, O_RDONLY);
	if (info->infile_no == -1)
		return (error_return(0, NULL, "Unable to read input file."));
	while (read(info->infile_no, buf, 1))
		write(info->out_now, buf, 1);
	close(info->infile_no);
	return (0);
}

int	read_stdin(t_token *token, t_info *info, int i)
{
	char	*ptr;

	ptr = NULL;
	while (ft_strncmp(ptr, token->input[i], ft_strlen(token->input[i]) + 1))
	{
		if (ptr)
		{
			ptr = env_var(ptr, info->env);
			write(info->out_now, ptr, ft_strlen(ptr));
			write(info->out_now, "\n", 1);
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
			if (out_file(token->output[i], info, token->append[i]))
				return (1);
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
		pipe(info->pipe_fd);
		info->in_now = info->pipe_fd[0];
		info->out_now = info->pipe_fd[1];
		if (token->heredoc[i])
			read_stdin(token, info, i);
		else
			if (in_file(token->input[i], info))
				return (1);
		if (token->input[++i])
		{
			close(info->in_now);
			close(info->out_now);
		}
	}
	return (0);
}
