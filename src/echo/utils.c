/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:48:33 by obibby            #+#    #+#             */
/*   Updated: 2023/02/01 09:36:51 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execute.h"

char	*insert_exit_stat(char *arg, char **env, int i)
{
	char	*var;
	char	*exit_stat;
	int		j;
	int		x;

	exit_stat = ft_itoa(g_status.exit_status);
	var = ft_calloc(ft_strlen(arg) + ft_strlen(exit_stat) - 1, sizeof(char *));
	j = 0;
	while (arg[j] && j < i - 1)
	{
		var[j] = arg[j];
		j++;
	}
	x = 0;
	while (exit_stat[x])
		var[j++] = (char)exit_stat[x++];
	while (arg[++i])
		var[j++] = arg[i];
	var[j] = '\0';
	free(exit_stat);
	free(arg);
	return (var);
}

char	*rep_str(char *arg, char *var, char *env, int i)
{
	int	j;
	int	x;

	j = 0;
	x = 0;
	while (arg[j] && j < i - 1)
	{
		var[j] = arg[j];
		j++;
	}
	while (arg[i] && arg[i] != ' ' && arg[i] != '$')
		i++;
	while (env[x])
		var[j++] = env[x++];
	while (arg[i])
		var[j++] = arg[i++];
	free(arg);
	return (var);
}

char	*str_rem_var(char *arg, int i)
{
	int		j;
	int		x;
	char	*var;

	j = 0;
	x = 0;
	while (arg[i + j] && arg[i + j] != ' ')
		j++;
	var = ft_calloc(ft_strlen(arg) + 1 - j, sizeof(char));
	if (!var)
		return (null_return(NULL, 0, NULL, "Memory allocation fail\n"));
	while (arg[x] && x < i)
	{
		var[x] = arg[x];
		x++;
	}
	j += x;
	while (arg[j])
		var[x++] = arg[j++];
	free(arg);
	return (var);
}

char	*str_rep_var(char *arg, char **env, int i)
{
	int		x;
	int		y;
	int		j;
	char	*var;

	x = -1;
	while (env[++x])
	{
		y = 0;
		j = 0;
		while (env[x][y] && arg[i + y]
			&& env[x][y] == arg[i + y] && env[x][y] != '=')
			y++;
		if (y != 0 && env[x][y++] == '='
			&& (!arg[i + y - 1] || arg[i + y - 1] == ' '))
		{
			while (env[x][y + j])
				j++;
			var = ft_calloc(ft_strlen(arg) + j + 1 - y, sizeof(char));
			if (!var)
				return (null_return(NULL, 0, NULL, "Memory allocation fail\n"));
			return (rep_str(arg, var, &env[x][y], i));
		}
	}
	return (NULL);
}
