#include "minishell.h"

// comment for a test

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
		token->path = ft_strdup(adress);
		// printf("local\n");

		return (0);
	}
	return (1);
}

// int		check_path(t_mini *mini, t_token *token, char *cmd)

int		check_path(t_mini *mini, t_token *token)
{
	char	**adress;
	char	*str;
	int		i;
	char	*clean;
	char	*tmp_adr;

// 	printf("cmd name %s\n", token->cmd_name);
	// printf("CHECK PATH %s\n", str);

	tmp_adr = get_env_str(mini->env, "PATH");
	if(tmp_adr)
		tmp_adr += 5;
	adress = ft_split_or(tmp_adr, ':');

	i = 0;
	clean = 0;
	
	while (adress[i])
	{
// 		printf("ENTERED\n");
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
	// printf("token->cmd_args[0]%s \n", token->cmd_args[0]);
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


int	get_args(t_mini *mini, char *str, t_token *token)
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
	int		bg;
	int		end;
	
	// n = 0;
	i = 0;
	m = 0;
	tk_counter = 0;
	head = token;
	open_q = false;
	mini->tokens = token;
	// printf("in get_args\n");
	bg = 0;
	end = 0;

	while (str && str[i])
	{
		if (tk_counter > 0)
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
			token->heredoc = 0;
			token->append = 0;
			token->input = NULL;
			token->output = NULL;
			// token->appnd = NULL;
			// token->hered = NULL;
		}
		
		// if (!open_q)
		// 	str = get_cmd_name(mini, str, token);
		// if (str[i] == '\"' || str[i] == '\'')
		// if ((str[i] == '\"' || str[i] == '\'') && open_q == false)

		if ((str[i] == '\"' || str[i] == '\''))
		{
			open_q = true;
			q_char = str[i];
			i++;

		}
		// printf("get_cmd_name %s\n", str);
		while (str[i] && str)
		{
			if (open_q == true && str[i] == q_char)
			{
				open_q = false;
				q_char = 0;

			}
			else if ((str[i] == '\"' || str[i] == '\'') && open_q == false)

			// else if ((str[i] == '\"' || str[i] == '\''))
			{
				open_q = true;
				q_char = str[i];
				i++;
			}
			if (open_q == true && str[i] == q_char)
			{
				open_q = false;
				q_char = 0;

				// end = i;
			}
			if ((str[i] == '|' || str[i] == '<' || str[i] == '>') && open_q == true)
				i++;
			else if ((str[i] == '|' || str[i] == '<' || str[i] == '>')  && open_q == false)
			{
				if (str[i] == '<')
				{
					token->type = str[i];
					str[i] = 0;
					i++;
					if (str[i] == '<')
					{
						str[i] = 0;
						i++;
						if (!ft_islower(str[i]) && !ft_isdigit(str[i]) && !ft_isalpha(str[i]) && str[i] != ' ')
							return (1);
						else
							i--;
						token->type = 'd';
					}
					else if (!ft_islower(str[i]) && !ft_isdigit(str[i]) && !ft_isalpha(str[i]) && str[i] != ' ')
						return (1);
					else
						i--;
				}
				else if (str[i] == '>')
				{
					token->type = str[i];
					str[i] = 0;

					i++;
					if (str[i] == '>')
					{
						printf("*** quote for output %i\n", open_q);
						str[i] = 0;
						i++;
						if (!ft_islower(str[i]) && !ft_isdigit(str[i]) && !ft_isalpha(str[i]) && str[i] != ' ')
							return (1);
						else
							i--;						
						token->type = 'a';
					}
					else if (!ft_islower(str[i]) && !ft_isdigit(str[i]) && !ft_isalpha(str[i]) && str[i] != ' ')
						return (1);
					else
						i--;
				}
				if (!token->type)
					token->type = str[i];
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
	return (0);
	// printf("done\n");
}



int	check_args(t_mini *mini)
{
	t_token *tmp;
	char	*ltmp;
	char	**new_args;
	int		i;

	tmp = mini->tokens;
	ltmp = NULL;
	while(tmp)
	{
		if (tmp->type == 'd')
		{
			if (tmp->cmd_args && tmp->cmd_args[0] && tmp->cmd_args[0][0])
			{
				// printf("in if 1 \n");
				// printf("%i\n", tmp->cmd_args[0][0]);
				if (!tmp->next->cmd_args || !tmp->next->cmd_args[0])
					return (1);
				// // tmp->next->cmd_args[0] = tmp->cmd_args[0];
				new_args = malloc(sizeof(char) * 3);
				new_args[0] = ft_strdup(tmp->cmd_args[0]);
				i = 0;
				// while (tmp->cmd_args[i])
				// {
				// 	// free(tmp->cmd_args[i]);
				// 	// tmp->cmd_args[0] = NULL;
				// 	i++;
				// }
				// free(tmp->cmd_args);
				tmp->cmd_args = NULL;
				new_args[1] = ft_strdup(tmp->next->cmd_args[0]);
				new_args[2] = 0;


				// i = 0;
				// while(tmp->next->cmd_args[i])
				// {
				// 	free(tmp->next->cmd_args[i]);
				// 	i++;
				// }
				// free(tmp->next->cmd_args);
				tmp->next->cmd_args = new_args;

				// tmp->next->type = 'd';
				// break ;

				
			}
			else if (!tmp->next->cmd_args || !tmp->next->cmd_args[0] || !tmp->next->cmd_args [1])
				return (1);
			else
			{
				// printf("in else 2 \n");

				ltmp = tmp->next->cmd_args[0];

				tmp->next->cmd_args[0] = tmp->next->cmd_args[1];
				tmp->next->cmd_args[1] = ltmp;
				// printf("tmp->next->cmd_args[0] %s\n", tmp->next->cmd_args[0]);

			}
			
			
		}
		tmp = tmp->next;
	}
	// printf("left \n");
	return(0);
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
	str = readline("👑𝖒 𝖎𝖓𝖎𝖘𝖍𝖊𝖑𝖑 ▸ ");

	if (!str || !str[0])
		return (0);

	token = malloc(sizeof(t_token));
	token->next = NULL;
	token->prev = NULL;

	token->path = NULL;
	token->cmd_args = NULL;
	token->cmd_name = NULL;
	token->type = 0;
	token->heredoc = 0;
	token->append = 0;
	token->input = NULL;
	token->output = NULL;
	// token->appnd = NULL;
	// token->hered = NULL;
	token->input = NULL;
	token->output = NULL;

	
	
	if(get_args(mini, str, token))
	{
		free(str);

		printf("invalid special charachter syntax\n");
		return (1);
	}
	free(str);



	// if (check_args(mini))
	// {
		// printf("invalid special charachter use\n");
	// 	return (1);
	// }
	// printf("past check_args\n");

	if (fin_token(mini))
	{
		printf("invalid special charachter use 2\n");
		return (1);

	}

	tmp = mini->tokens;
	while (tmp)
	{
		if (tmp->input && !tmp->append)
		{
			i = 0;

			while (tmp->input[i])
			{
				i++;
			}
			tmp->append= calloc(i, sizeof(int));
		}
		if (tmp->output && !tmp->heredoc)
		{
			i = 0;

			while (tmp->output[i])
			{
				i++;
			}
			tmp->heredoc= calloc(i, sizeof(int));
		}
		tmp = tmp->next;
	}



	// printf("index %s", token->cmd_args[i]);


	// printf("past fin_token\n");

	// i = 0;

	// j = 0;
	// token = mini->tokens;
	// 	while(token)
	// {
	// 	i = 0;
	// 	printf("token%i\n", j);

	// 	if (token->cmd_args)
	// 	{

	// 		while(token->cmd_args[i])
	// 		{
	// 			printf("arg[%i] = %s\n", i, token->cmd_args[i]);
	// 			i++;
	// 		}
	// 		printf("path %s\n", token->path);
			

	// 	}
	// 	i = 0;
	// 	while (token->input && token->input[i])
	// 	{
	// 		printf("input %s\n", token->input[i]);
	// 		i++;
	// 	}
	// 	i = 0;
	// 	while (token->output && token->output[i])
	// 	{
	// 		printf("output %s\n", token->output[i]);
	// 		i++;
	// 	}
		
	// 	printf("token type = %c\n", token->type);
	// 	token = token->next;
	// 	printf("\n");
	// 	j++;
		
	// }
	
	glue(mini->tokens);
	// printf("past printing\n");

	// tmp = mini->tokens;
	// i = 0;
	// j = 0;
	// while(tmp)
	// {
	// 	i = 0;
		// printf("final token %s\n", tmp->cmd_name);

	// 	while(tmp->cmd_args[i])
	// 	{
			// printf("final arg %s\n", tmp->cmd_args[i]);

	// 		while(tmp->cmd_args[i][j])
	// 		{
				// printf(" %d\n", tmp->cmd_args[i][j]);
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
	// printf("past check_env_vr\n");

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
	// printf("past quotes\n");

	mng_spaces(mini);
	// printf("past spaces\n");

	mng_quotes(mini);

	tmp = mini->tokens;

	while (tmp)
	{
		if (tmp->input)
			mng_quotes_light(tmp->input);
		if (tmp->output)
			mng_quotes_light(tmp->output);
		tmp = tmp->next;
	}

	// printf("past quotes2\n");


// ^^^^check_path

	tmp = mini->tokens;
	// printf("%s\n", tmp->cmd_name);

	while (tmp)
	{
		if (tmp->cmd_args)
		{		
			if (check_path(mini, tmp))
			{
				printf("no such command\n");
				return (1);
			}
		}
			// tmp->cmd_name = tmp->cmd_args[0];
		tmp = tmp->next;

	}

	// printf("YAAAAY\n");

	// tmp = mini->tokens;
	// i = 0;
	// j = 0;
	// while(tmp)
	// {
	// 	i = 0;
		// printf("final token %s\n", tmp->cmd_name);

	// 	while(tmp->cmd_args[i])
	// 	{
	// 		j = 0;
			// printf("final arg %s\n", tmp->cmd_args[i]);
			// printf("path %s\n", tmp->path);
	// 		while(tmp->cmd_args[i][j])
	// 		{
				// printf(" %d\n", tmp->cmd_args[i][j]);
	// 			j++;

	// 		}
			// printf("n of args %d\n", i);

	// 		i++;
	// 	}
	// 	tmp = tmp->next;
	// }


	// i = 0;

	// j = 0;
	// token = mini->tokens;
	// while(token)
	// {
	// 	i = 0;
	// 	printf("token%i\n", j);

	// 	if (token->cmd_args)
	// 	{

	// 		while(token->cmd_args[i])
	// 		{
	// 			printf("arg[%i] = %s@\n", i, token->cmd_args[i]);
	// 			i++;
	// 		}
	// 		printf("path %s\n", token->path);
			

	// 	}
	// 	i = 0;
	// 	while (token->input && token->input[i])
	// 	{
	// 		printf("input %s\n", token->input[i]);
	// 		i++;
	// 	}
	// 	i = 0;
	// 	while (token->output && token->output[i])
	// 	{
	// 		printf("output %s\n", token->output[i]);
	// 		i++;
	// 	}
	// 	i = 0;
	// 	if (token->append)
	// 	{
	// 		while (i < 5)
	// 		{
	// 			printf("app arr %i\n", token->append[i]);
	// 			i++;
	// 		}
	// 	}
	// 	i = 0;
	// 	if (token->heredoc)
	// 	{
	// 		while (i < 5)
	// 		{
	// 			printf("her arr %i\n", token->heredoc[i]);
	// 			i++;
	// 		}
	// 	}
	
	// 	printf("token type = %c\n", token->type);
	// 	token = token->next;
	// 	printf("\n");
	// 	j++;
		
	// }

	
	return (0);
	
}

// < file1 cat 

// token0
// args = cat (command for <, > will always be in the same token as type)
// type = <

// //here we can eather put files in args, or use the strust 
// // that we are going to use for << filea
// token1
// args =  file