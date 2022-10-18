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

void	free_d_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr && arr[0])
	{
		while (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
	}
	if (arr)
		free(arr);
	arr = NULL;
}

int	free_token_light(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->cmd_args != NULL)
			free_d_arr(tokens->cmd_args);
		if (tokens->input)
			free_d_arr(tokens->input);
		if (tokens->output)
			free_d_arr(tokens->output);
		if (tokens->path)
			free(tokens->path);
		if (tokens)
			free(tokens);
		tokens = tmp;
	}
	tokens = NULL;
	return (0);
}

int	free_token(t_mini *mini)
{
	t_token	*tmp;

	tmp = mini->tokens;
	while (mini->tokens)
	{
		tmp = mini->tokens->next;
		if (mini->tokens->cmd_args != NULL)
			free_d_arr(mini->tokens->cmd_args);
		if (mini->tokens->input)
			free_d_arr(mini->tokens->input);
		if (mini->tokens->output)
			free_d_arr(mini->tokens->output);
		if (mini->tokens->heredoc)
			free(mini->tokens->heredoc);
		if (mini->tokens->append)
			free(mini->tokens->append);
		if (mini->tokens->path)
			free(mini->tokens->path);
		free(mini->tokens);
		mini->tokens = tmp;
	}
	mini->tokens = NULL;
	return (0);
}

int	free_env(t_mini *mini)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = mini->env;
	while (mini->env)
	{
		tmp = mini->env->next;
		i = 0;
		if (mini->env->str)
		{
			free(mini->env->str);
		}
		free(mini->env);
		mini->env = tmp;
	}
	return (0);
}
