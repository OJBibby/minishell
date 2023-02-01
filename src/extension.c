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

void	check_q_ext(t_ext *ex, t_token *tmp, int *i, int *j)
{
	if ((tmp->cmd_args[*i][*j] == '\"'
		|| tmp->cmd_args[*i][*j] == '\'') && !ex->q_dom)
	{
		ex->q_dom = tmp->cmd_args[*i][*j];
		(*j)++;
	}
	if ((ex->q_dom) && (tmp->cmd_args[*i][*j] == ex->q_dom))
		ex->q_dom = 0;
}

void	check_s(t_ext *ex, int *i, int *j, t_token *tmp)
{
	if (ex->s && ex->s[0])
	{
		ex->t = tmp->cmd_args[*i];
		tmp->cmd_args[*i] = ft_strjoin(ex->clean, ex->s);
		free(ex->t);
		free(ex->clean);
	}
	else
	{
		ex->t = tmp->cmd_args[*i];
		tmp->cmd_args[*i] = ft_strdup(ex->clean);
		if (ex->t)
			free(ex->t);
		if (ex->clean)
			free(ex->clean);
	}
}

int	if_question_mark(t_ext *ex, int *i, int *j, t_token *tmp)
{
	ex->s = tmp->cmd_args[*i] + *j;
	ex->index = ft_strchr_nb(tmp->cmd_args[*i], '$');
	ex->ext = ft_itoa(g_status.exit_status);
	if (!ex->ext)
		return (1);
	ex->s += 1;
	ex->clean = ft_insert(tmp->cmd_args[*i], ex->ext, -1, ex->index);
	check_s(ex, i, j, tmp);
	if (ex->ext)
		free(ex->ext);
	*j = -1;
	ex->q_dom = 0;
	return (0);
}

int	ext_main_body(t_ext *ex, int *i, int *j, t_mini *mini)
{
	t_token	*tmp;

	tmp = mini->tm;
	ex->n = 0;
	check_q_ext(ex, tmp, i, j);
	if ((tmp->cmd_args[*i][*j] == '$') && (ex->q_dom == '\"' || !ex->q_dom))
	{
		(*j)++;
		if (tmp->cmd_args[*i][*j] == '?')
		{
			if (if_question_mark(ex, i, j, tmp))
				return (1);
		}
		else if (!tmp->cmd_args[*i][*j])
			return (-1);
		else
		{
			ex->exit = if_var(ex, i, j, mini);
			if (ex->exit)
				return (-1);
			else if (ex->exit == -1)
				return (0);
		}
	}
	return (0);
}

int	check_env_vr(t_mini *mini)
{
	int		i;
	int		j;
	t_ext	ex;

	while (mini->tm)
	{
		i = 0;
		ex.q_dom = 0;
		while (mini->tm->cmd_args && mini->tm->cmd_args[i])
		{
			j = 0;
			while (mini->tm->cmd_args[i][j])
			{
				ex.exit = ext_main_body(&ex, &i, &j, mini);
				if (ex.exit == 1)
					return (1);
				else if (ex.exit == -1)
					break ;
				j++;
			}
			i++;
		}
		mini->tm = mini->tm->next;
	}
	return (0);
}
