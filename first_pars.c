#include "minishell.h"

int	separate(char *str, t_token *token)
{
	int	i;
	int	arg;
	char	**tmp;
	char	*tmp_str;
	char	q_char;
	bool	open_q;
	// t_token *token;

	// token = tokens;
	i = 0;
	open_q = false;
	q_char = 0;
	// printf("in separate\n");
	while (str && str[i] && str[i] == ' ')
		str++; // !!!!!!!!!!!!!!!!!!
	if ((str[i] == '\"' || str[i] == '\''))
	{
		open_q = true;
		q_char = str[i];
		i++;

	}	
	while (str && str[i])
	{

		// while (str[i] && str)
		// {
		if (open_q == true && str[i] == q_char)
		{
			open_q = false;
			q_char = 0;

		}
		else if ((str[i] == '\"' || str[i] == '\'') && open_q == false)

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
		if (str[i] == ' ' && open_q == true)
			i++;
		else if (str[i] == ' ' && open_q == false)
		{
			i++;
			if (str[i] && str[i] == ' ')
			{
				while (str[i] == ' ')
					i++;
			}
			i--;				
			str[i] = 0;
			i++;
			// printf("the string is %s\n", str);
			// printf("the open_q is %i\n", open_q);

			tmp_str = str + i;
			token->cmd_args = add_string(token->cmd_args, str);
			if (tmp_str)
			{
				// if (str)
				// 	free(str);
				str = tmp_str;
				i = -1;
			}
			else
			{
				if (str)
					free(str);
				return (0);
			}
		}
		i++;
		if (!str[i])
		{
			token->cmd_args = add_string(token->cmd_args, str);
			// if (str)
			// 	free(str);
			return (0);

		}
			
		// }
		// if (i)
		// {
		// 	if (str[i] == ' ')
		// 		str[i] = 0;

		// 	i++;
		// 	tmp_str = str + i;
		// 	token->cmd_args = add_string(token->cmd_args, str);
		// 	if (tmp_str)
		// 	{
		// 		// if (str)
		// 		// 	free(str);
		// 		str = tmp_str;
		// 		i = 0;
		// 	}
		// 	else
		// 	{
		// 		if (str)
		// 			free(str);
		// 		return (0);
		// 	}
		// }
	}
	return (0);
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
	// while (str && str[i] && str[i] == ' ')
	// 	i++;
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
						// printf("*** quote for output %i\n", open_q);
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

		// token->cmd_args = ft_split(tmp, ' ', mini, token);
		separate(tmp, token);
		str += i;
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