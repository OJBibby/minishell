#include "minishell.h"

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
	// printf("my %s\n", mini->env->str);

	// printf("original %s\n", or_env[0]);
	return (head);
}


void    mng_sigint(int sig)
{
	if (sig == SIGINT)
		exit(0);
}

int	free_token(t_mini *mini)
{
	t_token	*tmp;
	int		i;
	// int		ccl;

	i = 0;
	// ccl = 0;
	tmp = mini->tokens;
	while(mini->tokens)
	{
		tmp = mini->tokens->next;
		// if (mini->tokens->cmd_name)
		// 	free(mini->tokens->cmd_name);
		i = 0;

		if (mini->tokens->cmd_args)
		{
			while(mini->tokens->cmd_args[i])
			{
				free(mini->tokens->cmd_args[i]);
				// printf("cmd_args[%i] freed\n", i);
				i++;
			}
			if (mini->tokens->cmd_args)
			{
				free(mini->tokens->cmd_args);
				// printf("cmd_args freed\n");
			}
		}
		if (mini->tokens->path)
		{
			// printf("in path\n");

			free(mini->tokens->path);
			// printf("path[%i] freed\n", i);
		}

		free(mini->tokens);
		mini->tokens = tmp;
		// printf("%i\n", ccl);
		// ccl++;
	}
	// if (tmp)
	// 	free(tmp);
	return (0);
}

int	free_env(t_mini *mini)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = mini->env;
	while(mini->env)
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


// function "parsing" returns 1 in case of an error
// if it returns 0, we move to your part – execution


int		main(int ac, char **av, char **env)
{
	t_mini	mini;
	

	mini.env = init_env(&mini, env);
	mini.tokens = NULL;
    while (1)
    {
		if(parsing(&mini))
			printf("string passed to the shell is not valid\n");
	    else
		{
			pipex(&mini, env);
		}
		free_token(&mini);
	}
	free_env(&mini);

}