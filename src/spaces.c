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

char	*ft_remove(char **str, int *j, char c)
{
	int		i;
	char	*ret;
	char	*tmp;
	int		n;

	i = 0;
	n = 0;
	ret = malloc(sizeof(char) * ft_strlen(*str));
	while ((*str)[n])
	{
		if (n != *j)
		{
			ret[i] = (*str)[n];
			i++;
			n++;
		}
		else
			n++;
	}
	ret[i] = 0;
	(*j)--;
	if (*str)
		free (*str);
	*str = NULL;
	return (ret);
}

void	spaces_main_body(t_token *tmp, int i)
{
	char	*clean;
	int		j;
	char	q_dom;

	j = 0;
	q_dom = 0;
	while (tmp->cmd_args[i][j])
	{
		if ((tmp->cmd_args[i][j] == '\"'
			|| tmp->cmd_args[i][j] == '\'') && !q_dom)
			q_dom = tmp->cmd_args[i][j];
		else if (q_dom && (tmp->cmd_args[i][j] == q_dom))
			q_dom = 0;
		else if ((tmp->cmd_args[i][j] == ' ') && !q_dom)
		{
			clean = ft_remove(&tmp->cmd_args[i], &j, ' ');
			tmp->cmd_args[i] = clean;
		}
		j++;
	}
}

int	mng_spaces(t_mini *mini)
{
	t_token	*tmp;
	int		i;

	tmp = mini->tokens;
	while (tmp)
	{
		i = 0;
		if (tmp->cmd_args)
		{
			while (tmp->cmd_args[i])
			{
				spaces_main_body(tmp, i);
				i++;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
