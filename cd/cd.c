/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:37:12 by obibby            #+#    #+#             */
/*   Updated: 2022/09/23 22:50:55 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

int	ft_cd(t_token *token, t_info *info)
{
	t_env	*env;
	int		retval;
	char	*str;

	close(info->out_now);
	close(info->in_now);
	if (!token->output)
	{
		if (!token->cmd_args[1] || !ft_strncmp(token->cmd_args[1], "~", 2))
		{
			env = get_env_node(info->env_ll, "HOME");
			str = ft_strdup(&env->str[5]);
			retval = chdir(str);
			free(str);
		}
		else
			retval = chdir(token->cmd_args[1]);
		if (retval)
		{
			printf("Error changing directory.\n");
			return (1);
		}
	}
	return (2);
}
