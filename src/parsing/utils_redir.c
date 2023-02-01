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

void	mod_heredoc(t_util *ut, int i)
{
	int		*tmp_int;

	tmp_int = ut->ret->heredoc;
	if (ut->old->type == '<')
		ut->ret->heredoc = add_int(ut->ret->heredoc, 0, i, ut->ilen);
	else
		ut->ret->heredoc = add_int(ut->ret->heredoc, 1, i, ut->ilen);
	(ut->ilen)++;
	if (tmp_int)
		free(tmp_int);
}

void	mod_append(t_util *ut, int i)
{
	int		*tmp_int;

	tmp_int = ut->ret->append;
	if (ut->old->type == '>')
		ut->ret->append = add_int(ut->ret->append, 0, i, ut->olen);
	else
		ut->ret->append = add_int(ut->ret->append, 1, i, ut->olen);
	ut->olen += i;
	if (tmp_int)
		free(tmp_int);
}

int	check_valid_args(t_util *ut)
{
	if (!ut->old->next || !ut->old->next->cmd_args
		|| !ut->old->next->cmd_args[0] || !ut->old->next->cmd_args[0][0])
	{
		free_token_light(ut->head);
		ut->head = NULL;
		return (1);
	}
	return (0);
}
