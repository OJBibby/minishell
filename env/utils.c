/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:34:31 by obibby            #+#    #+#             */
/*   Updated: 2022/10/14 11:14:30 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

int	check_env_input(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '=')
			break ;
		j++;
		if (!str[j])
			return (1);
	}
	return (0);
}

int	assign_args(t_token *token, char **new_args)
{
	int	i;
	int	j;

	i = 0;
	free(token->cmd_args[i]);
	while (token->cmd_args[++i])
	{
		new_args[i - 1] = ft_calloc(ft_strlen(token->cmd_args[i])
				+ 1, sizeof(char *));
		if (!new_args[i - 1])
			return (error_return(5, new_args, "Memory allocation fail."));
		j = -1;
		while (token->cmd_args[i][++j])
			new_args[i - 1][j] = token->cmd_args[i][j];
		new_args[i - 1][j] = 0;
		free(token->cmd_args[i]);
	}
	free(token->cmd_args[i]);
	free(token->cmd_args);
	token->cmd_args = new_args;
	return (0);
}

int	shift_args(t_token *token)
{
	int		i;
	char	**new_args;

	i = 1;
	while (token->cmd_args[i])
		i++;
	new_args = ft_calloc(i + 1, sizeof(char *));
	if (!new_args)
		return (1);
	new_args[i] = NULL;
	assign_args(token, new_args);
	return (0);
}

t_env	*free_copied_env(t_env *env)
{
	t_env	*next;
	int		dir;

	dir = 1;
	if (env && env->prev)
		dir = -1;
	while (env)
	{
		if (dir == 1)
			next = env->next;
		else
			next = env->prev;
		if (env->str)
			free(env->str);
		free(env);
		env = next;
	}
	return (NULL);
}

int	replace_var(char *var, t_env *env)
{
	free(env->str);
	env->str = NULL;
	env->str = ft_strdup(var);
	if (!env->str)
	{
		if (env->next && env->prev)
		{
			env->prev->next = env->next;
			env->next->prev = env->prev;
		}
		else if (env->next)
			env->next->prev = NULL;
		else if (env->prev)
			env->prev->next = NULL;
		return (error_return(1, env, "Memory allocation fail."));
	}
	return (0);
}
