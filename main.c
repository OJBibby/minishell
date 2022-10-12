#include "minishell.h"

int	g_exit;

t_env	*init_env(t_mini *mini, char **or_env)
{
	t_env	*env;
	t_env	*head;
	t_env	*tmp;
	int		i;

	env = malloc(sizeof(t_env));
	env->str = ft_strdup(or_env[0]);
	env->next = NULL;
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

void	mng_sigint(int sig)
{
	if (sig == SIGINT)
		exit(0);
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;

	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_int);
	rl_catch_signals = 0;
	mini.pid = getpid();
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
