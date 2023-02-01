/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:22:40 by obibby            #+#    #+#             */
/*   Updated: 2023/02/01 09:37:03 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execute.h"

int	check_exit_args(t_mini *mini)
{
	int	i;

	i = -1;
	if (mini->tokens->cmd_args[1][0] == '-')
	{
		i++;
		if (!mini->tokens->cmd_args[1][1])
		{
			printf("minishell: exit: numerical argument required\n");
			return (2);
		}
	}
	while (mini->tokens->cmd_args[1][++i])
	{
		if (mini->tokens->cmd_args[1][i] > '9'
			|| mini->tokens->cmd_args[1][i] < '0')
		{
			printf("minishell: exit: numerical argument required\n");
			return (2);
		}
	}
	if (mini->tokens->cmd_args[1])
		return (ft_atoi(mini->tokens->cmd_args[1]));
	return (0);
}

int	exit_shell(t_mini *mini)
{
	unsigned char	exit_val;
	int				i;

	printf("exit\n");
	if (mini->tokens->cmd_args[1] && mini->tokens->cmd_args[2])
		return (error_return(0, NULL, "minishell: exit: too many arguments"));
	if (mini->tokens->cmd_args[1])
		exit_val = check_exit_args(mini);
	clear_history();
	free_token(mini);
	free_env(mini);
	exit(exit_val);
}
