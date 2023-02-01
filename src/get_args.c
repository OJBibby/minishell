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

int	if_output(t_token *token, int *i, char **str)
{
	token->type = (*str)[*i];
	(*str)[*i] = 0;
	(*i)++;
	if ((*str)[*i] == '>')
	{
		(*str)[*i] = 0;
		(*i)++;
		if (!ft_islower((*str)[*i]) && !ft_isdigit((*str)[*i])
				&& !ft_isalpha((*str)[*i]) && (*str)[*i] != ' ')
			return (1);
		else
			(*i)--;
		token->type = 'a';
	}
	else if (!ft_islower((*str)[*i]) && !ft_isdigit((*str)[*i])
		&& !ft_isalpha((*str)[*i]) && (*str)[*i] != ' ')
		return (1);
	else
		(*i)--;
	return (0);
}

int	if_input(t_token *token, int *i, char **str)
{
	token->type = (*str)[*i];
	(*str)[*i] = 0;
	(*i)++;
	if ((*str)[*i] == '<')
	{
		(*str)[*i] = 0;
		(*i)++;
		if (!ft_islower((*str)[*i]) && !ft_isdigit((*str)[*i])
			&& !ft_isalpha((*str)[*i]) && (*str)[*i] != ' ')
			return (1);
		else
			(*i)--;
		token->type = 'd';
	}
	else if (!ft_islower((*str)[*i]) && !ft_isdigit((*str)[*i])
		&& !ft_isalpha((*str)[*i]) && (*str)[*i] != ' ')
		return (1);
	else
		(*i)--;
	return (0);
}

int	if_sp_chr(t_arg *ar, t_token *token, int *i, char **str)
{
	if ((*str)[*i] == '<')
	{
		if (if_input(token, i, str))
			return (1);
	}
	else if ((*str)[*i] == '>')
	{
		if (if_output(token, i, str))
			return (1);
	}
	if (!token->type)
		token->type = (*str)[*i];
	(*str)[*i] = 0;
	(*i)++;
	return (0);
}

int	main_loop(t_arg *ar, t_token *token, int *i, char **str)
{
	while ((*str)[*i] && *str)
	{
		if (ar->q_char && (*str)[*i] == ar->q_char)
			ar->q_char = 0;
		else if (((*str)[*i] == '\"' || (*str)[*i] == '\'') && !ar->q_char)
			ar->q_char = (*str)[*i];
		else if (((*str)[*i] == '|' || (*str)[*i] == '<'
			|| (*str)[*i] == '>') && !ar->q_char)
		{
			if (if_sp_chr(ar, token, i, str))
				return (1);
			break ;
		}
		(*i)++;
	}
	return (0);
}

int	get_args(t_mini *mini, char *str, t_token *token)
{
	int		i;
	t_token	*new;
	t_arg	ar;

	i = 0;
	ar.tk_counter = 0;
	ar.head = token;
	mini->tokens = token;
	ar.q_char = 0;
	while (str && str[i])
	{
		if (ar.tk_counter > 0)
		{
			new = init_token();
			new->prev = token;
			token->next = new;
			token = new;
		}
		if (main_loop(&ar, token, &i, &str))
			return (1);
		if (tokenize(&ar, token, &i, &str))
			break ;
	}
	mini->tokens = ar.head;
	return (0);
}
