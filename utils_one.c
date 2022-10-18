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

#include "minishell.h"

int	*add_int(int *arr, int nb, int q, int len)
{
	int	i;
	int	*tmp;
	int	n;

	i = 0;
	tmp = calloc((len + q), sizeof(int *));
	n = len + q;
	if (len > 0)
	{
		while (i < len)
		{
			tmp[i] = arr[i];
			i++;
		}
	}
	if (q == 1)
		tmp[i] = nb;
	else
	{
		while (q--)
			tmp[i++] = nb;
	}
	return (tmp);
}

char	**add_string(char **arr, char *str)
{
	int		i;
	char	**ret;
	int		j;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i])
			i++;
	}
	i += 2;
	ret = malloc(sizeof(char *) * i);
	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			ret[i] = ft_strdup(arr[i]);
			i++;
		}
	}
	ret[i++] = ft_strdup(str);
	ret[i] = 0;
	free_d_arr(arr);
	return (ret);
}

char	**copy_args(char **from, int n)
{
	char	**to;
	int		i;
	int		j;

	i = 0;
	j = n;
	while (from[n])
	{
		i++;
		n++;
	}
	to = malloc(sizeof(char *) * (i + 1));
	i = 0;
	n = j;
	while (from[n])
	{
		to[i] = ft_strdup(from[n]);
		i++;
		n++;
	}
	to[i] = NULL;
	return (to);
}

void	init_in_out(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->input && !tmp->append)
		{
			i = 0;
			while (tmp->input[i])
				i++;
			tmp->append = calloc(i, sizeof(int));
		}
		if (tmp->output && !tmp->heredoc)
		{
			i = 0;
			while (tmp->output[i])
				i++;
			tmp->heredoc = calloc(i, sizeof(int));
		}
		tmp = tmp->next;
	}
}

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->next = NULL;
	token->prev = NULL;
	token->path = NULL;
	token->cmd_args = NULL;
	token->type = 0;
	token->heredoc = NULL;
	token->append = NULL;
	token->input = NULL;
	token->output = NULL;
	return (token);
}
