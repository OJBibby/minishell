/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:11:55 by obibby            #+#    #+#             */
/*   Updated: 2022/10/15 15:21:42 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

int	add_env_var(char *var, t_env *env)
{
	int	i;
	int	j;

	if (env->str)
		return (replace_var(var, env));
	i = -1;
	while (var[++i])
	{
		if (var[i] == '=' && var[i + 1])
		{
			env->str = ft_strdup(var);
			if (!env->str)
				return (error_return(1, env, "Memory allocation fail."));
			break ;
		}
	}
	return (0);
}

char	*null_return(char **arr, int id, void *ptr, char *str)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	error_return(id, ptr, str);
	return (NULL);
}

void	free_joined(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*search_path_var(t_token *token, char **arr)
{
	int		i;
	char	*str;

	i = 0;
	while (arr[i])
	{
		str = ft_strjoin_slash(arr[i++], token->cmd_args[0]);
		if (!str)
			return (null_return(arr, 0, NULL, "Memory allocation fail."));
		if (access(str, F_OK) == 0)
			break ;
		if (!arr[i])
			return (null_return(arr, 1, str, "Command not found."));
		free(str);
	}
	return (str);
}

char	*search_path(t_token *token, t_info *info)
{
	int		i;
	char	*str;
	char	**arr;

	str = "PATH=";
	i = 0;
	while (info->env[i])
	{
		if (ft_strncmp(str, info->env[i], 5) == 0)
			break ;
		i++;
	}
	arr = ft_split_or(info->env[i], ':');
	if (!arr)
		return (null_return(NULL, 0, NULL, "Memory allocation fail."));
	str = search_path_var(token, arr);
	if (!str)
		return (NULL);
	free_joined(arr);
	return (str);
}
