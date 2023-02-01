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

#include "../inc/minishell.h"

void	valid_var(t_ext *ex, int *i, int *j, t_token *tmp)
{
	ex->s += ex->n;
	ex->clean = ft_insert(tmp->cmd_args[*i], ex->ext, ex->n, ex->index);
	if (ex->s)
	{
		ex->t = tmp->cmd_args[*i];
		tmp->cmd_args[*i] = ft_strjoin(ex->clean, ex->s);
		free(ex->t);
		free(ex->clean);
	}
	else
	{
		ex->t = tmp->cmd_args[*i];
		tmp->cmd_args[*i] = ex->clean;
		free(ex->t);
	}
	*j = -1;
	ex->q_dom = 0;
}

void	invalid_var(t_ext *ex, int *i, int *j, t_token *tmp)
{
	ex->clean = tmp->cmd_args[*i];
	(*j)--;
	ex->n++;
	tmp->cmd_args[*i] = extract(tmp->cmd_args[*i], *j, ex->n);
	if (ex->clean)
		free(ex->clean);
	*j = -1;
	ex->q_dom = 0;
}

int	if_var(t_ext *ex, int *i, int *j, t_mini *mini)
{
	ex->s = mini->tm->cmd_args[*i] + *j;
	ex->index = ft_strchr_nb(mini->tm->cmd_args[*i], '$');
	while ((ex->s[ex->n] >= 'A' && ex->s[ex->n] <= 'Z')
		|| (ex->s[ex->n] >= 'a' && ex->s[ex->n] <= 'z'))
		ex->n++;
	if (!ex->n)
	{
		ex->n++;
		if (!ex->s[ex->n])
			return (-1);
		else
		(*j)++;
		return (1);
	}
	ex->clean = ft_strndup(ex->s, ex->n);
	ex->ext = get_env_str(mini->env, ex->clean);
	if (ex->clean)
		free(ex->clean);
	if (!ex->ext)
		invalid_var(ex, i, j, mini->tm);
	else
		valid_var(ex, i, j, mini->tm);
	return (0);
}
