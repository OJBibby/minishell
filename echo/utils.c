/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:48:33 by obibby            #+#    #+#             */
/*   Updated: 2022/10/13 13:16:39 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

int	rep_str(char *arg, char *var, char *env, int i)
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
	arg = var;
	return (0);
}

int	str_rem_var(char *arg, char *var, int i)
{
	int	j;
	int	x;

	j = 0;
	x = 0;
	while (arg[i + j] && arg[i + j] != ' ')
		j++;
	var = ft_calloc(ft_strlen(arg) + 1 - j, sizeof(char));
	while (arg[x] && x < i)
	{
		var[x] = arg[x];
		x++;
	}
	j += x;
	while (arg[j])
		var[x++] = arg[j++];
	free(arg);
	arg = var;
	return (0);
}

int	str_rep_var(char *arg, char **env, char *var, int i)
{
	int	x;
	int	y;
	int	j;

	x = -1;
	while (env[++x])
	{
		y = 0;
		j = 0;
		while (env[x][y] && arg[i + y]
			&& env[x][y] == arg[i + y] && env[x][y] != '=')
			y++;
		if (y != 0 && env[x][y++] == '=')
		{
			while (env[x][y + j])
				j++;
			var = ft_calloc(ft_strlen(arg) + j + 1 - y, sizeof(char));
			if (!var)
				return (error_return(0, NULL, "Memory allocation fail\n"));
			return (rep_str(arg, var, &env[x][y], i));
		}
	}
	return (0);
}
