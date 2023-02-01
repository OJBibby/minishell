/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgreenpo <cgreenpo@student.42wolfsburg.de> +#+  +:+       +#+    	  */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:43:46 by cgreenpo            #+#    #+#           */
/*   Updated: 2022/10/14 12:30:24 by cgreenpo           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	in_condition_three(t_util *ut, int *i, int *j)
{
	char	**tmp_arr;

	if (check_valid_args(ut))
		return (1);
	if (ut->ret->input)
		free_d_arr(ut->ret->input);
	ut->ret->input = NULL;
	ut->ret->input = add_string(ut->ret->input, ut->old->next->cmd_args[0]);
	mod_heredoc(ut, 1);
	if (ut->old->next->cmd_args[1])
		ut->ret->cmd_args = copy_args(ut->old->next->cmd_args, 1);
	return (0);
}

void	in_condition_two(t_util *ut, int *i, int *j)
{
	char	**tmp_arr;
	int		ct;

	*i = 0;
	tmp_arr = add_string(ut->ret->input, ut->old->next->cmd_args[0]);
	ut->ret->input = tmp_arr;
	if (ut->old->next->cmd_args[1])
	{
		ct = 1;
		while (ut->old->next->cmd_args[ct])
		{
			ut->ret->cmd_args = add_string(ut->ret->cmd_args, \
			ut->old->next->cmd_args[ct]);
			ct++;
		}
	}
	mod_heredoc(ut, 1);
}

int	in_condition_one(t_util *ut, int *i, int *j)
{
	char	**tmp_arr;
	int		ct;

	tmp_arr = ut->ret->cmd_args;
	ut->ret->cmd_args = copy_args(ut->old->cmd_args, 0);
	if (tmp_arr)
		free(tmp_arr);
	if (ut->old->next->cmd_args && ut->old->next->cmd_args[0])
		ut->ret->input = add_string(ut->ret->input, ut->old->next->cmd_args[0]);
	else
		return (1);
	cp_args(ut);
	*i = 0;
	*j = ut->ilen;
	while (ut->ret->input[(*j)++])
		(*i)++;
	mod_heredoc(ut, *i);
	return (0);
}

int	redir_in(t_util *ut, int *i, int *j)
{
	char	**tmp_arr;
	int		*tmp_int;

	if (ut->old->cmd_args && ut->old->cmd_args[0] && ut->old->cmd_args[0][0])
	{
		if ((ut->old->prev && ut->old->prev->type != '<'
				&& ut->old->prev->type != '>' && ut->old->prev->type != 'd'
				&& ut->old->prev->type != 'a') || !ut->old->prev)
		{
			if (in_condition_one(ut, i, j))
				return (1);
		}
		else if (ut->old->prev->type == '<' || ut->old->prev->type == '>'
			|| ut->old->prev->type == 'd' || ut->old->prev->type == 'a')
			in_condition_two(ut, i, j);
	}
	else
	{
		if (in_condition_three(ut, i, j))
			return (1);
	}
	if (ut->old->next->type == '|')
		ut->ret->output = add_string(ut->ret->output, "|");
	return (0);
}
