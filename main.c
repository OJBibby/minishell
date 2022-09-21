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

int	free_token_light(t_token *tokens)
{
	t_token	*tmp;
	int		i;
	// int		ccl;

	i = 0;
	// ccl = 0;
	tmp = tokens;
	while(tokens)
	{
		tmp = tokens->next;
		// if (mini->tokens->cmd_name)
		// 	free(mini->tokens->cmd_name);
		i = 0;

		if (tokens->cmd_args)
		{
			while(tokens->cmd_args[i])
			{
				if (tokens->cmd_args[i] != NULL)
					free(tokens->cmd_args[i]);
				// printf("cmd_args[%i] freed\n", i);
				i++;
			}
			if (tokens->cmd_args)
			{
				free(tokens->cmd_args);
				// printf("cmd_args freed\n");
			}
		}
		i = 0;
		if (tokens->input)
		{
			while (tokens->input[i])
			{
				if (tokens->input[i])
					free(tokens->input[i]);
				i++;
			}
			if (tokens->input)
				free (tokens->input);

		}
		i = 0;
		if (tokens->output)
		{
			while (tokens->output[i])
			{
				if (tokens->output[i])
					free(tokens->output[i]);

				i++;
			}
			if (tokens->output)
				free(tokens->output);
		}
		if (tokens->path)
		{
			// printf("in path\n");

			free(tokens->path);
			// printf("path[%i] freed\n", i);
		}
		if (tokens)
			free(tokens);
		tokens = tmp;
		// printf("%i\n", ccl);
		// ccl++;
	}
	tokens = NULL;
	// if (tmp)
	// 	free(tmp);
	return (0);
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

		if (mini->tokens->cmd_args != NULL)
		{
			// while(mini->tokens->cmd_args[i] && mini->tokens->cmd_args[i][0])
			while(mini->tokens->cmd_args[i])

			{
				if (mini->tokens->cmd_args[i] != NULL)
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
		i = 0;
		if (mini->tokens->input)
		{
			while (mini->tokens->input[i])
			{
				if (mini->tokens->input[i])
					free(mini->tokens->input[i]);
				i++;
			}
			if (mini->tokens->input)
				free (mini->tokens->input);

		}
		i = 0;
		if (mini->tokens->output)
		{
			while (mini->tokens->output[i])
			{
				if (mini->tokens->output[i])
					free(mini->tokens->output[i]);

				i++;
			}
			if (mini->tokens->output)
				free(mini->tokens->output);
		}
		if (mini->tokens->heredoc)
			free(mini->tokens->heredoc);
		if (mini->tokens->append)
			free(mini->tokens->append);
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
	mini->tokens = NULL;
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
	// int		i;

	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_int);
	mini.env = init_env(&mini, env);
	mini.tokens = NULL;
	// i = 1;
    while (1)
    {
		if(parsing(&mini))
			printf("string passed to the shell is not valid\n");
	    else
			execute(&mini);
		free_token(&mini);
	}
	free_env(&mini);

}