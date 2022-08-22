#include "minishell.h"


int	check_quotes(char *str)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			counter++;
		i++;
	}
	if (!i)
		return (0);
	if (counter % 2)
		return (-1);
	else
		return (i);
}

int	check_local_adress(t_token *token, char	*adress, t_mini *mini)
{
	// if (ft_strchr(token->cmd_name, '~'))
	// {

	// }
	if (access(adress, F_OK) == 0)
	{
		token->path = adress;
		// printf("local\n");

		return (0);
	}
	return (1);
}

int		check_path(t_mini *mini, t_token *token)
{
	char	**adress;
	char	*str;
	int		i;
	char	*clean;
	char	*tmp_adr;

	// printf("cmd name %s\n", token->cmd_name);
	// printf("CHECK PATH %s\n", str);

	tmp_adr = get_env_str(mini->env, "PATH");
	if(tmp_adr)
		tmp_adr += 5;
	adress = ft_split_or(tmp_adr, ':');

	i = 0;
	clean = 0;
	
	while (adress[i])
	{
		// printf("ENTERED\n");
		// printf("%s\n", adress[i]);

		if (ft_strchr(token->cmd_args[0], '/'))
		{
			while (adress[i])
			{
				free(adress[i]);
				i++;
			}
			free(adress);
			return(check_local_adress(token, token->cmd_args[0], mini));

		}
		// printf("after\n");

		clean = adress[i];
		adress[i] = ft_strjoin(adress[i], "/"); //!!!
		free(clean);
		clean = adress[i];
		adress[i] = ft_strjoin(adress[i], token->cmd_args[0]);
		free(clean);

		// printf("%s\n", adress[i]);

		if (access(adress[i], F_OK) == 0)
		{
			token->path = ft_strdup(adress[i]);
			// printf("not local\n");
			i = 0;
			while (adress[i])
			{
				free(adress[i]);
				i++;
			}
			free(adress);
			return (0);
		}
		i++;
	}
	i = 0;
	while (adress[i])
	{
		free(adress[i]);
		i++;
	}
	free(adress);

	token->path = NULL;
	token->cmd_name = NULL;

	return (1);
}


char	*get_cmd_name(t_mini *mini, char *str, t_token *token)
{

	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	while (*str == ' ')
		str++;
	// printf("ver 1 %s\n", str);

	while (str[n] != ' ' && str[n] != 0 && str[n] != '|')
		n++;
	// printf("%i\n", n);

	token->cmd_name = strndup(str, n); //!!!
	// printf("token %s\n", token->cmd_name);

	str += n;
	// printf("ver 2 %s\n", str);

	return (str);
}

void	get_args(t_mini *mini, char *str, t_token *token)
{
	int	i;
	int	m;
	int	tk_counter;
	t_token	*new;
	t_token *head;
	char	*tmp;
	bool	open_q;
	char	q_char;
	char	**tmp_arr;
	
	// n = 0;
	i = 0;
	m = 0;
	tk_counter = 0;
	head = token;
	open_q = false;
	mini->tokens = token;
	// printf("in get_args\n");

	while (str && str[i])
	{
		if (tk_counter > 0)
		{
			new = malloc(sizeof(t_token));
			new->next = NULL;
			token->next = new;
			token = new;
			token->path = NULL;
			token->cmd_args = NULL;
			token->cmd_name = NULL;
		}
		
		// if (!open_q)
		// 	str = get_cmd_name(mini, str, token);
		if (str[i] == '\"' || str[i] == '\"')
		{
			open_q = true;
			q_char = str[i];

		}
		// printf("get_cmd_name %s\n", str);
		while (str[i] && str)
		{
			if (open_q == true && str[i] == q_char)
			{
				open_q = false;
			}
			else if (str[i] == q_char && open_q == false)
			{
				open_q = true;
			}
			if (str[i] == '|' && open_q == true)
				i++;
			else if (str[i] == '|' && open_q == false)
			{
				str[i] = 0;
				i++;
				break ;
			}
			i++;
		}
		tmp = str;
		// printf("before the first %s\n", tmp);
		// tmp = strndup(tmp, )
		// tmp_arr = token->cmd_args;
		// token->cmd_args[0] = token->cmd_name;
		// token->cmd_args++;
		token->cmd_args = ft_split(tmp, ' ', mini, token);
		// token->cmd_name = token->cmd_args[0];
		// token->cmd_args = tmp_arr;
		str += i;
		// printf("after the first %s\n", str);
		i = 0;
		if (!str || !str[i])
		{
			// printf("!str break\n");
			break ;
		}
		// printf("after the first %s\n", str);
		tk_counter++;
		// printf("done while\n");
	}
	// token = head;
	mini->tokens = head;

	// printf("done\n");
}




int	parsing(t_mini *mini)
{
	char	*str;
	char	*dup;
	t_token	*token;
	int		i;
	t_token	*tmp;
	int		j;
	

	// printf("in parsing\n");
	str = readline("👑𝖒𝖎𝖓𝖎𝖘𝖍𝖊𝖑𝖑 ▸ ");

	// if (!mini->prompt)
	// {
	// str = readline("👑𝖒𝖎𝖓𝖎𝖘𝖍𝖊𝖑𝖑 ▸ ");
		// str = strdup("echo hello hey | echo \"$USER\" \" \'   hi\'\"");
		// printf("%s\n", str);
	// 	mini->prompt = 1;
	// }

	if (!str || !str[0])
		return(1);

	token = malloc(sizeof(t_token));
	token->next = NULL;
	token->path = NULL;
	token->cmd_args = NULL;
	token->cmd_name = NULL;
	
	get_args(mini, str, token);
	free(str);

	// tmp = mini->tokens;
	// i = 0;
	// j = 0;
	// while(tmp)
	// {
	// 	i = 0;
	// 	// printf("final token %s\n", tmp->cmd_name);

	// 	while(tmp->cmd_args[i])
	// 	{
	// 		// printf("final arg %s\n", tmp->cmd_args[i]);

	// 		while(tmp->cmd_args[i][j])
	// 		{
	// 			// printf(" %d\n", tmp->cmd_args[i][j]);
	// 			j++;

	// 		}
	// 		i++;
	// 	}
	// 	tmp = tmp->next;
	// }

	tmp = mini->tokens;
	if (check_env_vr(mini))
	{
		printf("env variable does not exist\n");
		return (1);
	}
	tmp = mini->tokens;
	// printf("%s\n", tmp->cmd_name);
	while (tmp)
	{
		if (quotes(mini, tmp))
		{
			printf("quote syntax error\n");
			return (1);
		}
		tmp = tmp->next;

	}
	mng_spaces(mini);
	mng_quotes(mini);

// ^^^^check_path

	tmp = mini->tokens;
	// printf("%s\n", tmp->cmd_name);
	while (tmp)
	{
		if (check_path(mini, tmp))
		{
			printf("no such command\n");
			return (1);
		}
		tmp->cmd_name = tmp->cmd_args[0];
		tmp = tmp->next;

	}

	// printf("YAAAAY\n");

	tmp = mini->tokens;
	i = 0;
	j = 0;
	while(tmp)
	{
		i = 0;
		// printf("final token %s\n", tmp->cmd_name);

		while(tmp->cmd_args[i])
		{
			j = 0;
			// printf("final arg %s\n", tmp->cmd_args[i]);
			// printf("path %s\n", tmp->path);
			while(tmp->cmd_args[i][j])
			{
				// printf(" %d\n", tmp->cmd_args[i][j]);
				j++;

			}
			// printf("n of args %d\n", i);

			i++;
		}
		tmp = tmp->next;
	}


	// i = 0;
	// while(token)
	// {
	// 	i = 0;
	// 	printf("final token %s\n", token->cmd_name);

	// 	while(token->cmd_args[i])
	// 	{
	// 		printf("final arg %s\n", token->cmd_args[i]);
	// 		i++;
	// 	}
	// 	token = token->next;
	// }
	
	return (0);
	
}