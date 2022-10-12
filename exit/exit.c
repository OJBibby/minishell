/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:22:40 by obibby            #+#    #+#             */
/*   Updated: 2022/10/12 14:27:41 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

int	exit_shell(t_mini *mini)
{
	unsigned char	exit_val;
	int	i;
	
	exit_val = 0;
	printf("exit\n");
	if (mini->tokens->cmd_args[1] && mini->tokens->cmd_args[2])
		return (error_return(0, NULL, "minishell: exit: too many arguments"));
	if (mini->tokens->cmd_args[1])
	{
		i = -1;
		if (mini->tokens->cmd_args[1][0] == '-')
		{
			i++;
			if (!mini->tokens->cmd_args[1][1])
				printf("minishell: exit: numerical argument required\n");
		}
		while (mini->tokens->cmd_args[1][++i])
		{
			if (mini->tokens->cmd_args[1][i] > '9' || mini->tokens->cmd_args[1][i] < '0')
			{
				exit_val = 2;
				printf("minishell: exit: numerical argument required\n");
				break ;
			}
		}
	}
	if (exit_val == 0 && mini->tokens->cmd_args[1])
		exit_val = ft_atoi(mini->tokens->cmd_args[1]);
	clear_history();
	free_token(mini);
	free_env(mini);
	exit(exit_val);
}
