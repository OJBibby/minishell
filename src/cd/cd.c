/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:37:12 by obibby            #+#    #+#             */
/*   Updated: 2023/02/01 09:36:56 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execute.h"

char	*alloc_addr(t_token *token, t_info *info)
{
	t_env	*env;
	char	*str;

	str = NULL;
	if (!token->cmd_args[1] || token->cmd_args[1][0] == '~')
	{
		env = get_env_node(info->env_ll, "HOME");
		if (!env)
			return (null_return(NULL, 0, NULL, "minishell: cd: HOME not set"));
		str = ft_strdup(&env->str[5]);
	}
	else
		str = ft_strdup(token->cmd_args[1]);
	if (!str)
		printf("Memory allocation failed.");
	return (str);
}

int	ft_cd(t_token *token, t_info *info)
{
	char	*str;

	str = NULL;
	prepare_builtin(token, info);
	if (!token->output)
	{
		str = alloc_addr(token, info);
		if (!str)
			return (1);
		if (chdir(str))
		{
			printf("Error changing directory.\n");
			free(str);
			return (1);
		}
	}
	if (str)
		free(str);
	return (0);
}
