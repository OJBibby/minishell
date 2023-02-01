/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:43:46 by obibby            #+#    #+#             */
/*   Updated: 2023/02/01 09:37:14 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execute.h"

void	prepare_builtin(t_token *token, t_info *info)
{
	if (token->input && token->input[0][0] == '|')
	{
		exec_close_builtin(info);
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
	if (info->in_now > 0)
		close(info->in_now);
	info->in_now = -1;
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
