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

int	tokenize(t_arg *ar, t_token *token, int *i, char **str)
{
	ar->tmp = *str;
	separate(ar->tmp, token);
	*str += *i;
	*i = 0;
	if (!(*str) || !(*str)[*i])
		return (1);
	ar->tk_counter++;
	return (0);
}

void	init_new_token(t_token *token, t_token *new)
{
	new = malloc(sizeof(t_token));
	new->next = NULL;
	new->prev = token;
	token->next = new;
	token = new;
	token->path = NULL;
	token->cmd_args = NULL;
	token->cmd_name = NULL;
	token->type = 0;
	token->heredoc = NULL;
	token->append = NULL;
	token->input = NULL;
	token->output = NULL;
}

int	if_space(char **str, t_token *token, int *i)
{
	char	*tmp_str;

	(*i)++;
	if ((*str)[*i] && (*str)[*i] == ' ')
	{
		while ((*str)[*i] == ' ')
			(*i)++;
	}
	(*i)--;
	(*str)[*i] = 0;
	(*i)++;
	tmp_str = *str + *i;
	token->cmd_args = add_string(token->cmd_args, *str);
	if (tmp_str)
	{
		*str = tmp_str;
		*i = -1;
	}
	else
	{
		if (*str)
			free(*str);
		return (1);
	}
	return (0);
}

int	separate_main_loop(char **str, t_token *token, int *i)
{
	char	q_char;

	q_char = 0;
	while ((*str) && (*str)[*i])
	{
		if (q_char && (*str)[*i] == q_char)
			q_char = 0;
		else if (((*str)[*i] == '\"' || (*str)[*i] == '\'') && !q_char)
			q_char = (*str)[*i];
		else if ((*str)[*i] == ' ' && !q_char)
		{
			if (if_space(str, token, i))
				return (0);
		}
		(*i)++;
		if (!(*str)[*i] && ft_strlen(*str))
		{
			token->cmd_args = add_string(token->cmd_args, *str);
			return (0);
		}
	}
	return (0);
}

int	separate(char *str, t_token *token)
{
	int		i;

	i = 0;
	while (str && str[i] && str[i] == ' ')
		str++;
	return (separate_main_loop(&str, token, &i));
}
