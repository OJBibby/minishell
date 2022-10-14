/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:34:16 by obibby            #+#    #+#             */
/*   Updated: 2022/10/14 13:10:29 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

char *env_var(char *arg, char **env)
{
	int i;
	int n;
	char *var;

	i = -1;
	while (arg[++i])
	{
		var = NULL;
		if (arg[i] == '$')
		{
			i++;
			if (str_rep_var(arg, env, var, i))
				return (NULL);
			if (!var)
				str_rem_var(arg, var, i);
			i -= 2;
		}
	}
	return (arg);
}

int echo_write(t_token *token, t_info *info, int flags, int fd)
{
	int i;
	int j;

	if (flags == 0)
		i = 1;
	else
		i = 2;
	while (token->cmd_args[i])
	{
		j = -1;
		while (token->cmd_args[i][++j])
		{
			if (token->cmd_args[i][j] == '\n' && flags < 2)
				write(fd, "n", 2);
			else
				write(fd, &token->cmd_args[i][j], 1);
		}
		i++;
		if (token->cmd_args[i])
			write(fd, " ", 1);
	}
	if (flags == 0 || flags == 2)
		write(fd, "\n", 1);
	return (0);
}

int set_fd(t_token *token, t_info *info)
{
	if (token->output)
	{
		if (token->output[0][0] == '|')
			return (info->out_now);
		else
			return (info->outfile_no);
	}
	return (1);
}

int echo_set_flags(t_token *token)
{
	int i;
	int flags;

	i = 0;
	flags = 0;
	if (token->cmd_args[1] && token->cmd_args[1][0] == '-')
	{
		while (token->cmd_args[1][++i])
		{
			if (token->cmd_args[1][i] == 'n')
				flags += 1;
			else if (token->cmd_args[1][i] == 'e')
				flags += 2;
			else
			{
				flags = 0;
				break;
			}
		}
	}
	return (flags);
}

int ft_echo(t_token *token, t_info *info)
{
	int flags;
	int fd;

	flags = echo_set_flags(token);
	fd = set_fd(token, info);
	echo_write(token, info, flags, fd);
	if (token->output && token->output[0][0] != '|')
		close(info->outfile_no);
	return (0);
}
