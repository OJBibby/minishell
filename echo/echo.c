/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:34:16 by obibby            #+#    #+#             */
/*   Updated: 2022/09/12 23:07:35 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex/pipex.h"

int ft_echo(t_token *token, t_info *info)
{
	int i;
	int j;
	int	str;
	int flags;
	
	i = 1;
	flags = 0;
	str = 0;
	close(info->in_now);
	while (token->args[i] && token->args[i][0] == '-')
	{
		j = 0;
		while (token->args[i][++j])
		{
			if (token->args[i][j] != 'n' && token->args[i][j] != 'e')
			{
				str = 1;
				break ;
			}
		}
		if (str == 1)
			break ;
		j = 0;
		while (token->args[i][++j])
		{
			if (token->args[i][j] == 'n')
				flags += 1;
			else if (token->args[i][j] == 'e')
				flags += 2;
		}
		i++;
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
	j = -1;
	while (token->args[i] && token->args[i][++j])
	{
		if (token->args[i][j] == '\n' && flags < 2)
			write(1, "n", 2);
		else
			write(1, &token->args[i][j], 1);
	}
	if (flags == 0 || flags == 2)
		write(1, "\n", 1);
	return (2);
}
