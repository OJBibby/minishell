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

t_global	g_status;

t_env	*init_env(t_mini *mini, char **or_env)
{
	t_env	*env;
	t_env	*head;
	t_env	*tmp;
	int		i;

	env = malloc(sizeof(t_env));
	env->str = ft_strdup(or_env[0]);
	env->next = NULL;
	env->prev = NULL;
	mini->env = env;
	head = env;
	i = 1;
	while (or_env[i])
	{
		tmp = malloc(sizeof(t_env));
		tmp->str = ft_strdup(or_env[i]);
		tmp->next = NULL;
		tmp->prev = env;
		env->next = tmp;
		env = tmp;
		i++;
	}
	return (head);
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;

	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_int);
	rl_catch_signals = 0;
	mini.env = init_env(&mini, env);
	mini.tokens = NULL;
	mini.tm = NULL;
	ft_putstr_fd(GRT, 1);
	while (1)
	{
		if (parsing(&mini))
			ft_putstr_fd(B_ERR, 1);
		else
			execute(&mini);
		free_token(&mini);
	}
	free_env(&mini);
}
