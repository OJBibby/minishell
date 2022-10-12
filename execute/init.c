/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:41:00 by obibby            #+#    #+#             */
/*   Updated: 2022/10/11 19:26:00 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	init_files(t_token *token, t_info *info)
{
	token->input = NULL;
	if (token->input && token->input[0][0] != '|' && input_init(token, info))
		return (1);
	if (token->output && output_init(token, info))
		return (1);
	return (0);
}

int	count_args(t_token *token)
{
	int		i;
	t_token	*ptr;

	ptr = token;
	i = 0;
	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

void	init_array(t_mini *mini, t_info *info)
{
	info->token = mini->tokens;
	info->env_ll = mini->env;
	info->env = list_to_arr(mini->env);
	info->total_ops = count_args(info->token);
	info->done_ops = 0;
	info->stdout_fd = dup(STDOUT_FILENO);
	info->stdin_fd = dup(STDIN_FILENO);
	info->infile_no = -1;
	info->outfile_no = -1;
}
