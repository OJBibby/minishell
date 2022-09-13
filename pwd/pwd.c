/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:43:46 by obibby            #+#    #+#             */
/*   Updated: 2022/09/13 18:09:07 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex/pipex.h"

int	ft_pwd(t_token *token, t_info *info)
{
	char	*cwd;
	int		i;

	close(info->in_now);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		printf("Error retrieving working directory.\n");
		return (1);
	}
	if (token->output && token->output[0] == '|')
	{
		dup2(info->out_now, STDOUT_FILENO);
		close(info->out_now);
	}
	else if (token->output)
	{
		dup2(info->outfile_no, STDOUT_FILENO);
		close(info->outfile_no);
	}
	i = 0;
	while (cwd[i])
		write(1, &cwd[i++], 1);
	write(1, "\n", 1);
	free(cwd);
	return (2);
}
