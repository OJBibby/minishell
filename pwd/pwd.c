/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:43:46 by obibby            #+#    #+#             */
/*   Updated: 2022/09/20 13:03:48 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex/pipex.h"

int	ft_pwd(t_token *token, t_info *info)
{
	char	*cwd;
	int		i;
	int		fd;

	close(info->in_now);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		printf("Error retrieving working directory.\n");
		return (1);
	}
	fd = info->stdout_fd;
	if (token->output && token->output[0][0] == '|')
		fd = info->out_now;
	else if (token->output)
		fd = info->outfile_no;
	i = 0;
	while (cwd[i])
		write(fd, &cwd[i++], 1);
	write(fd, "\n", 1);
	free(cwd);
	return (2);
}
