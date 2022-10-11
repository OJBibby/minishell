/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:37:12 by obibby            #+#    #+#             */
/*   Updated: 2022/10/11 19:34:57 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

int	ft_cd(t_token *token, t_info *info)
{
	t_env	*env;
	char	*str;

	str = NULL;
	if (!token->output)
	{
		if (!token->cmd_args[1] || token->cmd_args[1][0] == '~')
		{
			env = get_env_node(info->env_ll, "HOME");
			if (!env)
				return (error_return(0, NULL, "minishell: cd: HOME not set"));
			str = ft_strjoin(&env->str[5], &token->cmd_args[1][1]);
		}
		else
			str = ft_strdup(token->cmd_args[1]);
		if (!str)
			return (error_return(0, NULL, "Unable to allocate memory."));
		if (chdir(str))
		{
			printf("Error changing directory.\n");
			free (str);
			return (1);
		}
	}
	free (str);
	return (0);
}
