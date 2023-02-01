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

int	check_q(char **arr, int i)
{
	int		j;
	char	q_dom;

	j = 0;
	q_dom = 0;
	while (arr[i][j])
	{
		if (q_dom && arr[i][j] == q_dom)
		{
			arr[i] = ft_remove(&arr[i], &j, q_dom);
			q_dom = 0;
		}
		else if ((arr[i][j] == '\"' || arr[i][j] == '\'') && !q_dom)
		{
			q_dom = arr[i][j];
			arr[i] = ft_remove(&arr[i], &j, q_dom);
		}
		j++;
		if (!arr[i] || !arr[i][j])
			break ;
	}
	return (0);
}

int	mng_quotes_light(char **arr)
{
	t_token	*tmp;
	int		i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			check_q(arr, i);
			i++;
		}
	}
	return (0);
}

int	quotes_main_loop(int i, int *j, t_quo *q, t_token *tmp)
{
	while ((tmp->cmd_args[i][*j] && (!q->dom_op && !q->dom_cl))
		|| ((q->dom_cl && q->dom_op) && q->dom == 0))
	{
		if (tmp->cmd_args[i][*j] == '\"' || tmp->cmd_args[i][*j] == '\'')
		{
			if (q->dom_cl && q->dom_op)
				q->dom = tmp->cmd_args[i][*j];
			else if (!q->dom_op && !q->dom_cl)
			{
				q->dom = tmp->cmd_args[i][*j];
				q->dom_op = true;
			}
			q->dom_cl = false;
			(*j)++;
			break ;
		}
		(*j)++;
		if (!tmp->cmd_args[i][*j])
			break ;
	}
	return (0);
}

int	quotes_mini_loop(int i, int *j, t_quo *q, t_token *tmp)
{
	while (tmp->cmd_args[i][*j] && (q->dom_op == true && !q->dom_cl))
	{
		if (tmp->cmd_args[i][*j] == q->dom)
		{
			q->dom_cl = true;
			q->dom = 0;
			(*j)++;
			break ;
		}
		(*j)++;
	}
	return (0);
}

int	quotes(t_token *tmp)
{
	int		i;
	int		j;
	t_quo	q;

	q.dom_cl = false;
	q.dom_op = false;
	q.dom = 0;
	i = 0;
	j = 0;
	if (tmp->cmd_args)
	{
		while (tmp->cmd_args[i])
		{
			j = 0;
			while (tmp->cmd_args[i][j])
			{
				quotes_main_loop(i, &j, &q, tmp);
				quotes_mini_loop(i, &j, &q, tmp);
			}
			i++;
		}
	}
	return (!((q.dom_cl && q.dom_op) || (!q.dom_cl && !q.dom_op)));
}
