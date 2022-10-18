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

int	part_one(t_mini *mini)
{
	t_token	*tmp;

	tmp = mini->tokens;
	mng_spaces(mini);
	if (fin_token(mini))
		return (ft_putstr_fd(SPC, 1));
	init_in_out(mini->tokens);
	mini->tm = mini->tokens;
	check_env_vr(mini);
	tmp = mini->tokens;
	while (tmp)
	{
		if (quotes(tmp))
			return (ft_putstr_fd(QUO, 1));
		tmp = tmp->next;
	}
	return (0);
}

int	part_two(t_mini *mini)
{
	t_token	*tmp;

	tmp = mini->tokens;
	while (tmp)
	{
		if (tmp->cmd_args)
			mng_quotes_light(tmp->cmd_args);
		if (tmp->input)
			mng_quotes_light(tmp->input);
		if (tmp->output)
			mng_quotes_light(tmp->output);
		tmp = tmp->next;
	}
	clean_args(mini->tokens);
	return (0);
}

int	part_three(t_mini *mini)
{
	t_token	*tmp;

	tmp = mini->tokens;
	while (tmp)
	{
		if (tmp->cmd_args)
		{	
			if (!check_builtin(tmp->cmd_args))
			{
				if (check_path(mini, tmp))
				{
					ft_putstr_fd(CMD, 1);
					return (1);
				}
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

void	good_exit(t_mini *mini)
{
	ft_putstr_fd(BYE, 1);
	free_env(mini);
	exit(1);
}

int	parsing(t_mini *mini)
{
	char	*str;
	t_token	*tmp;

	str = readline("👑𝖒 𝖎𝖓𝖎𝖘𝖍𝖊𝖑𝖑 ▸ ");
	if (!str)
		good_exit(mini);
	else if (str && !str[0])
	{
		free(str);
		return (0);
	}
	add_history(str);
	mini->tokens = init_token();
	if (get_args(mini, str, mini->tokens))
	{
		free(str);
		return (ft_putstr_fd(SYN, 1));
	}
	free(str);
	if (part_one(mini) || part_two(mini) || part_three(mini))
		return (1);
	return (0);
}
