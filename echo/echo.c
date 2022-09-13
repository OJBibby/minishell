/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:34:16 by obibby            #+#    #+#             */
/*   Updated: 2022/09/13 22:38:43 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex/pipex.h"

int	echo_write(t_token *token, int flags, int fd)
{
	int	i;
	int	j;

	if (flags == 0)
		i = 1;
	else
		i = 2;
	j = -1;
	if (token->args[i])
	{
		while (token->args[i][++j])
		{
			if (token->args[i][j] == '\n' && flags < 2)
				write(fd, "n", 2);
			else
				write(fd, &token->args[i][j], 1);
		}
		if (flags == 0 || flags == 2)
			write(fd, "\n", 1);
	}
	return (0);
}

int	echo_set_fd(t_token *token, t_info *info)
{
	int	fd;

	fd = 1;
	if (token->output && token->output[0] == '|')
		fd = info->out_now;
	else if (token->output)
		fd = info->outfile_no;
	return (fd);
}

int	echo_set_flags(t_token *token)
{
	int	i;
	int	flags;

	i = 0;
	flags = 0;
	if (token->args[1] && token->args[1][0] == '-')
	{
		while (token->args[1][++i])
		{
			if (token->args[1][i] == 'n')
				flags += 1;
			else if (token->args[1][i] == 'e')
				flags += 2;
			else
			{
				flags = 0;
				break ;
			}
		}
	}
	return (flags);
}

int	ft_echo(t_token *token, t_info *info)
{
	int	flags;
	int	fd;

	flags = echo_set_flags(token);
	fd = echo_set_fd(token, info);
	echo_write(token, flags, fd);
	return (2);
}
