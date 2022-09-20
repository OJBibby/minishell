/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 21:34:16 by obibby            #+#    #+#             */
/*   Updated: 2022/09/20 16:15:26 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex/pipex.h"

char	*env_var(char *arg, char **env)
{
	int		j;
	int		i;
	int		x;
	int		y;
	int		v;
	int		dif;
	char	*var;

	i = -1;
	while (arg[++i])
	{
		var = NULL;
		if (arg[i] == '$')
		{
			i++;
			x = -1;
			while (env[++x])
			{
				y = 0;
				j = 0;
				v = i;
				while (env[x][y] && arg[i + y] && env[x][y] == arg[i + y] && env[x][y] != '=')
					y++;
				if (y != 0 && env[x][y++] == '=')
				{
					while (env[x][y + j])
						j++;
					var = ft_calloc(ft_strlen(arg) + j + 1 - y, sizeof(char));
					j = 0;
					while (arg[j] && j < i - 1)
					{
						var[j] = arg[j];
						j++;
					}
					while (arg[v] && arg[v] != ' ' && arg[v] != '$')
						v++;
					dif = y - j;
					while (env[x][y])
						var[j++] = env[x][y++];
					while (arg[v])
						var[j++] = arg[v++];
					i += y - dif - 2;
					free(arg);
					arg = var;
					break ;
				}
			}
			if (!var)
			{
				j = 0;
				x = 0;
				y = 0;
				while (arg[i + j] && arg[i + j] != ' ')
					j++;
				var = ft_calloc(ft_strlen(arg) + 1 - j, sizeof(char));
				while (arg[x] && x < i)
					var[y++] = arg[x++];
				j = j + x;
				while (x < j)
					x++;
				while (arg[x])
					var[y++] = arg[x++];
				i--;
				free(arg);
				arg = var;
			}
		}
	}
	return (arg);
}

int	echo_write(t_token *token, t_info *info, int flags, int fd)
{
	int	i;
	int	j;

	if (flags == 0)
		i = 1;
	else
		i = 2;
	j = -1;
	while (token->cmd_args[i])
	{
		while (token->cmd_args[i][++j])
		{
			/*if (token->cmd_args[i][j] == '$')
				env_var(token->cmd_args[i], j, info->env);*/
			if (token->cmd_args[i][j] == '\n' && flags < 2)
				write(fd, "n", 2);
			else
				write(fd, &token->cmd_args[i][j], 1);
		}
		i++;
		j = -1;
		if (token->cmd_args[i])
			write(fd, " ", 1);
	}
	if (flags == 0 || flags == 2)
		write(fd, "\n", 1);
	return (0);
}

int	echo_set_fd(t_token *token, t_info *info)
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

int	echo_set_flags(t_token *token)
{
	int	i;
	int	flags;

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
	echo_write(token, info, flags, fd);
	return (2);
}
