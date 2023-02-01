/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:41:00 by obibby            #+#    #+#             */
/*   Updated: 2023/02/01 09:35:57 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execute.h"

int	init_files(t_token *token, t_info *info)
{
	if (token->input && (token->input[0][0] != '|'
		|| token->input[1]) && input_init(token, info))
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
	info->copied_env = NULL;
	info->env = list_to_arr(mini->env);
	info->total_ops = count_args(info->token);
	info->done_ops = 0;
	info->stdout_fd = dup(STDOUT_FILENO);
	info->stdin_fd = dup(STDIN_FILENO);
	info->infile_no = -1;
	info->outfile_no = -1;
	info->out_now = -1;
	info->in_now = -1;
	info->input_in = -1;
	info->input_out = -1;
}
