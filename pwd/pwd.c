/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:43:46 by obibby            #+#    #+#             */
/*   Updated: 2022/10/14 14:55:15 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

void	prepare_builtin(t_token *token, t_info *info)
{
	prepare_output(token, info);
	if (token->input && token->input[0][0] == '|')
	{
		pipe(info->pipe_fd);
		info->in_now = info->pipe_fd[0];
		info->out_now = info->pipe_fd[1];
	}
}

int	ft_pwd(t_token *token, t_info *info)
{
	char	*cwd;
	int		i;
	int		fd;

	prepare_builtin(token, info);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		printf("Error retrieving working directory.\n");
		return (1);
	}
	fd = set_fd(token, info);
	i = 0;
	while (cwd[i])
		write(fd, &cwd[i++], 1);
	write(fd, "\n", 1);
	free(cwd);
	return (0);
}
