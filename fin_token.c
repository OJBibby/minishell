#include "minishell.h"


int	rearrange(t_glue glue, t_token *token)
{
	char	**tmp;
	char	**ret;
	int		i;
	int		j;
	int		x;
	int		y;
	char	*str;
	int		n;
	int	res;

	i = 0;
	j = 0;

	// printf("in rearrange\n");
	while (token->cmd_args[i])
		i++;

	x = glue.end_arg - glue.bg_arg + 1;
	y = i - x + 1;

	if (glue.end_chr != (ft_strlen(token->cmd_args[glue.end_arg] - 1)))
		y++;
	if (glue.bg_chr > 0)
		y++;
	// printf("d arr %i\n", y + 1);

	ret = malloc(sizeof(char *) * (y + 1));
	
	ret[y] = NULL;
	j = glue.bg_arg;
	y = glue.bg_chr;
	// printf("%i\n", glue.bg_arg);
	i = 0;
	while(token->cmd_args && token->cmd_args[j] && j <= glue.end_arg)
	{
		// printf("%s \n", token->cmd_args[j]);
		if (j == glue.bg_arg)
		{
			while (token->cmd_args[j][y])
			{
				y++;
				i++;
			}
			j++;
		}
		y = 0;
		while(token->cmd_args[j] && token->cmd_args[j][y] && j != glue.end_arg)
		{
			// printf("** %c \n", token->cmd_args[j][y]);
			y++;
			i++;
		}
		if (j == glue.end_arg)
		{
			while (token->cmd_args[j][y] && y <= glue.end_chr)
			{
				// printf("** %c \n", token->cmd_args[j][y]);

				y++;
				i++;
			}
		}
		j++;
	}

	// printf("str len %i\n", i + 1);
	str = malloc(sizeof(char) * (i + 1));
	str[i] = 0;
	j = glue.bg_arg;
	i = glue.bg_chr;
	n = 0;

	while(token->cmd_args[j] && j <= glue.end_arg)
	{
		if (glue.bg_arg == glue.end_arg)
		{
			while(token->cmd_args[j][i] && i <= glue.end_chr)
			{
				// printf("** fr = %c \n", token->cmd_args[j][y]);

				str[n] = token->cmd_args[j][i];
				// printf("** to = %c \n", str[n]);

				n++;
				i++;
			}
			str[n] = 0;
			break ;
		}
		else
		{

		
	
			while (j != glue.end_arg)
			{
				if (j == glue.bg_arg)
					i = glue.bg_chr;
				else
				{
					i = 0;
				}
				// printf("from %s\n", token->cmd_args[j]);
				while(token->cmd_args[j][i])
				{
					
					str[n] = token->cmd_args[j][i];
					n++;
					i++;
				}
				j++;

			}
			// printf("final string %s\n", str);

			if(j == glue.end_arg)
			{
				i = 0;
				while (token->cmd_args[j][i] && i <= glue.end_chr)
				{
					str[n] = token->cmd_args[j][i];
					n++;
					i++;
				}
				break ;
			}
		}
	}
	// printf("final string %s\n", str);
	// j = glue.bg_arg;
	// i = glue.bg_chr;
	n = 0;
	j = 0;
	i = 0;
	while(token->cmd_args[j])
	{
		while (j < glue.bg_arg)
		{
			ret[n] = ft_strdup(token->cmd_args[j]);
			j++;
			n++;
		}
		if (j == glue.bg_arg)
		{
			if (glue.bg_chr > 0)
			{
				ret[n] = strndup(token->cmd_args[j], glue.bg_chr); //!!!!!!!!!!!!!!
				n++;
				while (j < glue.end_arg)
					j++;
			}

			ret[n] = str;
			n++;

		}
		if (j == glue.end_arg)
		{
			if (glue.end_chr != (ft_strlen(token->cmd_args[j] - 1)))
			{
				// printf("in != strlen \n");
				ret[n] = ft_strdup(token->cmd_args[j] + (glue.end_chr + 1)); //!!!!!!!!!!!!!!
				res = n;

				n++;
				j++;

			} 
			else
			{
				res = n;

			}
			
			while(token->cmd_args && token->cmd_args[j])
			{
				// printf("token->cmd_args[j] %s \n", token->cmd_args[j]);
				if(token->cmd_args[j])
					ret[n] = ft_strdup(token->cmd_args[j]);
				n++;
				j++;
			}	
		}
		

	}

	free_d_arr(token->cmd_args);
	token->cmd_args = ret;

	i = 0;

	while (token->cmd_args[i])
	{
		// printf("arg %s \n", token->cmd_args[i]);
		i++;
	}

	// printf("EXIT REARRANGE\n");
	return (res);

	

}

void	glue(t_token *tokens)
{
	int	i;
	int	j;
	int	arg;
	int	chr;
	t_glue	glue;
	t_token	*token;


	bool	open_q;
	char	q_char;

	i = 0;
	j = 0;
	token = tokens;

	glue.end_arg = 0;
	glue.end_chr = 0;
	glue.bg_arg = 0;
	glue.bg_chr = 0;
	// printf("in glue\n");
	while (token)
	{
		i = 0;
		open_q = false;
		q_char = 0;
		// printf("index %s", token->cmd_args[i]);
		while (token->cmd_args && token->cmd_args[i])
		{
			j = 0;
			// printf("index %s\n", token->cmd_args[i]);

			while (token->cmd_args[i] && token->cmd_args[i][j])
			{
				// printf("index %i", i);
				if ((token->cmd_args[i][j] == '\"' || token->cmd_args[i][j] == '\'') && open_q == false)
				{
					open_q = true;
					q_char = token->cmd_args[i][j];
					glue.bg_arg = i;
					glue.bg_chr = j;
					j++;

				}

				if (open_q == true && token->cmd_args[i][j] == q_char)
				{
					open_q = false;
					glue.end_arg = i;
					glue.end_chr = j;
					// printf("glue %i %i %i %i\n", glue.bg_arg, glue.bg_chr, glue.end_arg, glue.end_chr);
					i = rearrange(glue, token);
					// printf("after rearrange\n");
					my_print(token);
					// printf("new i = %i ", i);
					j = 0;
					// break ;
				}
				else if ((token->cmd_args[i][j] == '\"' || token->cmd_args[i][j] == '\'') && open_q == false)
				{
					open_q = true;
					glue.bg_arg = i;
					glue.bg_chr = j;
					j++;
				}
				else
					j++;
				// j++;
			}
			i++;
		}
		token = token->next;

	}
}

int	*add_int(int *arr, int nb, int q, int len)
{
	int	i;
	int *tmp;
	int	n;
	int	d;
	

	i = 0;
	// printf("len = %i\n", len);
	// printf("q = %i\n", q);
	// printf("nb = %i\n", nb);

	tmp = calloc((len + q), sizeof(int*)); 
	// tmp = malloc(sizeof(int*) * (len + q))''
	n = len + q;
	// while (i < n)
	// {
	// 	tmp[i] = 0;
	// 	i++;
	// }
	// i = 0;
	if (len > 0)
	{
		while (i < len)
		{
			tmp[i] = arr[i];
			// printf("from %i to %i \n", tmp[i], arr[i]);
			i++;
		}

	}

	if (q == 1)
	{
		tmp[i] = nb;

	}
	else
	{
		while (q--)
		{
			tmp[i] = nb;
			i++;
		}
		// tmp[0] = 1;
	}
	i = 0;
	// tmp[len] = nb;
	while (i < n)
	{
		// printf("app arr %i\n", tmp[i]);
		i++;
	}	
	return (tmp);
}

void	free_d_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr && arr[0])
	{
		while(arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
	}
	free(arr);
	arr = NULL;
}

void	my_print(t_token *token)
{
	int i, j;
	i = 0;

	j = 0;

	// printf("FIN token%i\n", j);

	if (token->cmd_args)
	{

		while(token->cmd_args[i])
		{
			// printf("arg[%i] = %s\n", i, token->cmd_args[i]);
			i++;
		}	// while (token->input && token->input[i])
	// {
	// 	printf("input %s\n", token->input[i]);
	// 	i++;
	// }
	// i = 0;
	// while (token->output && token->output[i])
	// {
	// 	printf("output %s\n", token->output[i]);
	// 	i++;
	// }
		// printf("path %s\n", token->path);
		
		

	}
	i = 0;

	// printf("append %i\n", token->append);
	// printf("heredoc %i\n", token->heredoc);			
	// printf("token type = %c\n", token->type);
	token = token->next;
	// printf("\n");
	j++;
		
}

char	**add_string(char **arr, char *str)
{
	int	i;
	char	**ret;
	int	j;

	// printf("add_string start\n");
	i = 0;
	if (!arr || !arr[i])
		i = 2;
	else
	{
		while (arr[i])
			i++;
		i += 2;

	}
	// printf(" %i\n", i);


	
	// printf("add_string mid 1\n");

	ret = malloc(sizeof(char *) * i);

	i = 0;
	if (arr)
	{
		while(arr[i])
		{
			// printf("from %s\n", arr[i]);

			ret[i] = ft_strdup(arr[i]);
			// printf("to %s\n", ret[i]);

			i++;
		}
	}
	// printf("add_string mid\n");
	ret[i] = ft_strdup(str);
	// printf(" %s\n", ret[i]);
	// printf(" %s\n", ret[0]);

	i++;
	ret[i] = 0;

	// printf(" %i\n", i);
	// printf(" %s\n", ret[0]);
	// printf(" %s\n", ret[0]);
	// printf(" %s\n", ret[1]);

	//FREE ARR !!!!!!!!!!!
	// printf("add_string end\n");
	i = 0;
	if (arr)
	{
		while(arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
	return (ret);
}

char	**copy_args(char **from, int n)
{
	char **to;
	int		i;
	int		j;


	i = 0;
	j = n;

	// from += n;
	while(from[n])
	{

		i++;
		n++;

	}
	// printf("the i is %i\n", i);
	to = malloc(sizeof(char *) * (i + 1));

	// to[0] = ft_strdup("hi");
	i = 0;
	n = j;
	while(from[n])
	{
		to[i] = ft_strdup(from[n]);
		// printf("arg %i %s \n", i, from[n]);
		i++;
		n++;
	}
	to[i] = NULL;
	// to[0] = ft_strdup(from[0]);
	// if(to[1])
	// 	to[1] = ft_strdup(from[1]);


	return (to);

}



int	fin_token(t_mini *mini)
{
	t_token	*old;
	t_token	*ret;
	t_token	*new;
	t_token	*head;
	char	**tmp_arr;
	int	i;
	char	**to;
	int		j;
	int		*tmp_int;
	int		olen;
	int		ilen;
	

	old = mini->tokens;

	ret = NULL;
	while(old)
	{

		// printf("in while old\n");
		new = malloc(sizeof(t_token));
		new->next = NULL;
		new->prev = NULL;

		new->path = NULL;
		new->cmd_args = NULL;
		new->cmd_name = NULL;
		new->type = 0;
		// new->heredococ = 0;
		// new->append = 0;
		new->input = NULL;
		new->output = NULL;
		new->append = NULL;
		new->heredoc = NULL;
		// printf("past malloc\n");

		if (!ret)
		{
			// printf("in !ret\n");

			ret = new;
			head = new;
		}
		else
		{
			// printf("in else\n");

			new->prev = ret;
			ret->next = new;
			ret = ret->next;
		}
		if (ret->prev)
		{
			// printf("in ret->prev\n");
			if (!ret->prev->output)
			{
				free_token_light(ret);
				return (1);

			}
			ret->input = malloc(sizeof(char) * 2);
			// printf("ret->prev->output[0] %s\n", ret->prev->output[0]);

			ret->input[0] = ft_strdup("|");
			ret->input[1] = 0;
		}
		// printf("past while old\n");
		olen = 0;
		ilen = 0;
		while (old->type != '|' && old)
		{


			// printf("in !| \n");
			if (old->type == '<' || old->type == 'd')
			{
				if (old->cmd_args && old->cmd_args[0] && old->cmd_args[0][0])
				{
					

					if ((old->prev && old->prev->type != '<' && old->prev->type != '>' && old->prev->type != 'd' && old->prev->type != 'a') || !old->prev)
					{
						tmp_arr = ret->cmd_args;
						ret->cmd_args = copy_args(old->cmd_args, 0);
						free(tmp_arr);
						// printf("< if arg  %s\n", old->cmd_args[0]);
	
						tmp_arr = ret->input;
						ret->input = copy_args(old->next->cmd_args, 0);
						if (tmp_arr)
							free_d_arr(tmp_arr);
						i = 0;
						j = ilen;
						while (ret->input[j])
						{
							j++;
							i++;
						}
						tmp_int = ret->heredoc;
						if (old->type == '<')
							ret->heredoc = add_int(ret->heredoc, 0, i, ilen);
						else
							ret->heredoc = add_int(ret->heredoc, 1, i, ilen);
						ilen += i;
						if (tmp_int)
							free(tmp_int);
						// printf("NEW LEN %i\n", ilen);
					}
					else if (old->prev->type == '<' || old->prev->type == '>' || old->prev->type == 'd' || old->prev->type == 'a')
					{

						i = 0;
						// printf("in old->next->type == '>'\n");
						// printf("string or %s\n", ret->input[0]);

						while(old->next && old->next->cmd_args && old->next->cmd_args[i])
						{
							// printf("ADD input %s\n", old->next->cmd_args[i]);
							tmp_arr = add_string(ret->input, old->next->cmd_args[i]);
							// printf("string or 1   %s\n", tmp_arr[i]);
							// if (ret->input && ret->input[0])
							// 	free_d_arr(ret->input);
							ret->input = tmp_arr;
							i++;
							// printf("string or %s\n", ret->input[0]);
							// ret->input = add_string(ret->input, old->next->cmd_args[0]);
							// printf("LEEEN %i\n", ilen);
							tmp_int = ret->heredoc;

							if (old->type == '<')
								ret->heredoc = add_int(ret->heredoc, 0, 1, ilen);
							else
								ret->heredoc = add_int(ret->heredoc, 1, 1, ilen);
							ilen++;
							if (tmp_int)
								free(tmp_int);


						}

					}
					
				}
				else
				{
					if (!old->next || !old->next->cmd_args || !old->next->cmd_args[0])
					{
						free_token_light(head);

						return (1);


					}
					// if (old->next->cmd_args[1])
					// {
					// 	if (ret->cmd_args)
					// 		free_d_arr(ret->cmd_args);
					// 	tmp_arr = copy_args(old->next->cmd_args, 1);
					// 	ret->cmd_args = tmp_arr;


						
						
					// }
					if (ret->input)
						free_d_arr(ret->input);					
					// ret->input = malloc(sizeof(char *) * 2);
					// ret->input[0] = ft_strdup(old->next->cmd_args[0]);
					// ret->input[1] = 0;
					ret->input = add_string(ret->input, old->next->cmd_args[0]);

					tmp_int = ret->heredoc;
					
					if (old->type == '<')
						ret->heredoc = add_int(ret->heredoc, 0, 1, ilen);
					else
						ret->heredoc = add_int(ret->heredoc, 1, 1, ilen);
					ilen++;
					if (tmp_int)
						free(tmp_int);
					if (old->next->cmd_args[1])
						ret->cmd_args = copy_args(old->next->cmd_args, 1);


				}
					
				if (old->next->type == '|')
				{
					ret->output = add_string(ret->output, "|");
				}

			}
			
			else if (old->type == '>' || old->type == 'a')
			{
				// if (old->type == 'a')
				// 	ret->append = 1;
				// if (old->type == 'a')
				// 	ret->append = add_int(ret->append, 1);
				// else
				// 	ret->append = add_int(ret->append, 0);

				if (old->cmd_args && old->cmd_args[0] && old->cmd_args[0][0])
				{

					// printf("in old->cmd etc\n");


					if ((old->prev && old->prev->type != '<' && old->prev->type != '>' && old->prev->type != 'd' && old->prev->type != 'a') || !old->prev)
 					{
						// printf("in !<\n");

						tmp_arr = ret->cmd_args;
						ret->cmd_args = copy_args(old->cmd_args, 0);
						if (tmp_arr)
							free_d_arr(tmp_arr);


						// printf("in prev type\n");

						// printf("old->cmd_args[0] %s\n", old->cmd_args[0]);
						if (!old->next || !old->next->cmd_args[0] || !old->next->cmd_args[0][0])
						{
							free_token_light(head);
							return (1);
						}
						
						tmp_arr = copy_args(old->next->cmd_args, 0);
						if (ret->output)
							free_d_arr(ret->output);
						ret->output = tmp_arr;
						i = 0;
						j = olen;
						while (ret->output[j])
						{
							j++;
							i++;
						}
						tmp_int = ret->append;
						if (old->type == '>')
							ret->append = add_int(ret->append, 0, i, olen);
						else
							ret->append = add_int(ret->append, 1, i, olen);
						olen += i;
						if (tmp_int)
							free(tmp_int);
						// printf("NEW LEN %i\n", olen);
						
					}
					else if (old->prev->type == '>' || old->prev->type == '<' || old->prev->type == 'a' || old->prev->type == 'd')
					{
						// printf("in old->prev->type == '>'\n");

						i = 0;
						// printf("in old->next->type == '>'\n");
	
						if (!old->next || !old->next->cmd_args || !old->next->cmd_args[0] || !old->next->cmd_args[0][0])
						{
							// printf("890\n");
							
							free_token_light(head);
							head = NULL;
							return (1);
						}
						if (old->next->cmd_args[1])
						{
							// printf("990\n");

							tmp_arr = ret->cmd_args;
							ret->cmd_args = copy_args(old->next->cmd_args, 1);
							if (tmp_arr)
								free_d_arr(tmp_arr);
						}
						// printf("790\n");

						ret->output = add_string(ret->output, old->next->cmd_args[0]);
						// printf("LEEEN %i\n", olen);
						tmp_int = ret->append;
						if (old->type == '>')
							ret->append = add_int(ret->append, 0, 1, olen);
						else
							ret->append = add_int(ret->append, 1, 1, olen);
						olen++;
						if (tmp_int)
							free(tmp_int);
					}

					if (old->next->type == '|')
					{
						// printf("-- in old next type \n");
						ret->output = add_string(ret->output, "|");
					}		
				}
				else
				{
					if (!old->next || !old->next->cmd_args[0])
					{
						free_token_light(head);
						return (1);
					}
					ret->output = add_string(ret->output, old->next->cmd_args[0]);
					tmp_int = ret->append;
					if (old->type == '>')
						ret->append = add_int(ret->append, 0, 1, olen);
					else
						ret->append = add_int(ret->append, 1, 1, olen);
					olen++;
					if (tmp_int)
						free(tmp_int);
					if (old->next->cmd_args[1])
						ret->cmd_args = copy_args(old->next->cmd_args, 1);

				}


			}
			else if (!old->type && !old->next)
			{
				// printf("in ! !\n");
				if (old->prev && (old->prev->type == '<' || old->prev->type == '>' || old->prev->type == 'a' || old->prev->type == 'd'))
				{

					// my_print(head);
					// printf("EXIT\n");
					free_token(mini);					

					mini->tokens = head;

					return (0);

				}

				free_d_arr(ret->cmd_args);
				ret->cmd_args = copy_args(old->cmd_args, 0);

				free_token(mini);

				mini->tokens = head;
				// printf("before leaving %s\n", mini->tokens->cmd_args[0]);

				return (0);

			}
			else
			{
				free_token_light(head);
				return (1);
			}

			old = old->next;
			// my_print(ret);
			// if (!ret->append)
			// {
			// 	ret->append = malloc(sizeof(int));
			// 	// ret->append = NULL;
			// }

		}
		// printf("out !| \n");

		if (old->type == '|')
		{
			if (!old->cmd_args || !old->cmd_args[0] || !old->cmd_args[0][0] || !old->next || !old->next->cmd_args)
			{
				free_token_light(head);
				// printf("exit error | \n");
				return (1);

			}
			if ((old->prev && old->prev->type != '<' && old->prev->type != '>' && old->prev->type != 'd' && old->prev->type != 'a') || !old->prev)
			{

				ret->cmd_args = copy_args(old->cmd_args, 0);

				tmp_arr = malloc(sizeof(char *) * 2);
				tmp_arr[0] = ft_strdup("|");
				tmp_arr[1] = 0;

				ret->output = tmp_arr;
				// printf("in output %s\n", ret->output[0]);

				old = old->next;
			}
			else if (old->prev && (old->prev->type == '>' || old->prev->type == 'a'))
			{
			//	printf("old prev output type \n");
			//	printf("ret->output %s %s\n", ret->output[0], ret->output[1]);
				old = old->next;

			}
			else if (old->prev && (old->prev->type == '<' || old->prev->type == 'd'))
			{
				old = old->next;

			}
			else
			{
				tmp_arr = malloc(sizeof(char *) * 2);
				tmp_arr[0] = ft_strdup("|");
				tmp_arr[1] = 0;
	
				ret->output = tmp_arr;
				// printf("in output %s\n", ret->output[0]);
				old = old->next;

			}

			
		}
		
	
	}

	// printf("done | \n");
	// printf("token or %s\n", mini->tokens->cmd_args[0]);


	return (0);

}