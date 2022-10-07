#include "minishell.h"


int	mng_quotes_light(char **arr)
{
	t_token	*tmp;
	int	i;
	int j;
	char	q_dom;
	// char	*ext;
	char	*clean;
	// printf("MANAGE QUOTES\n");

	i = 0;
	j = 0;
	q_dom = 0;
	if (arr)
	{

		while(arr[i])
		{
			j = 0;
			while(arr[i][j])
			{
				// printf("before if %c\n", q_dom);

				if((arr[i][j] == '\"' || arr[i][j] == '\'') && !q_dom)
				{
					// printf("ENTERED if\n");

					q_dom = arr[i][j];
					clean = arr[i];
					arr[i] = ft_remove_q(arr[i], &j, q_dom);
					free(clean);
					j++;
					// printf("here %c\n", q_dom);
				}
				if(q_dom && arr[i][j] == q_dom)
				{
					clean = arr[i];
					arr[i] = ft_remove_q(arr[i], &j, q_dom);
					// if (!tmp->cmd_args[i] || !tmp->cmd_args[i][0])
					// 	tmp->cmd_args[i] = NULL;
					if (clean)
						free(clean);
					q_dom = 0;
				}
				// printf("it was %c\n", tmp->cmd_args[i][j]);

				j++;
				// printf("it is %c\n", tmp->cmd_args[i][j]);

				if (!arr[i] || !arr[i][j])
				// if (!tmp->cmd_args[i][j])
					break ;
				
			}
			i++;
		}
	}
	return (0);
}

// int	mng_quotes(t_mini *mini)
// {
// 	t_token	*tmp;
// 	int	i;
// 	int j;
// 	char	q_dom;
// 	// char	*ext;
// 	char	*clean;

// 	tmp = mini->tokens;
// 	// printf("MANAGE QUOTES\n");
// 	q_dom = 0;

// 	while (tmp)
// 	{
// 		i = 0;
// 		j = 0;

// 		q_dom = 0;
// 		if (tmp->cmd_args)
// 		{

		
// 			while(tmp->cmd_args[i])
// 			{
// 				j = 0;
// 				while(tmp->cmd_args[i][j])
// 				{
// 					// printf("before if %c\n", q_dom);

// 					if((tmp->cmd_args[i][j] == '\"' || tmp->cmd_args[i][j] == '\'') && !q_dom)
// 					{
// 						// printf("ENTERED if\n");
// 						printf("1 option\n");

// 						q_dom = tmp->cmd_args[i][j];
// 						clean = tmp->cmd_args[i];
// 						printf("before %s\n", tmp->cmd_args[i]);
// 						tmp->cmd_args[i] = ft_remove_q(tmp->cmd_args[i], &j, q_dom);
// 						free(clean);
// 						printf("after %s\n", tmp->cmd_args[i]);

// 						// j++;
// 						printf("char j %c\n", tmp->cmd_args[i][j]);

// 						printf("here %c\n", q_dom);
// 					}
// 					if(q_dom && tmp->cmd_args[i][j] == q_dom)
// 					{
// 						printf("2 option\n");
// 						clean = tmp->cmd_args[i];
// 						tmp->cmd_args[i] = ft_remove_q(tmp->cmd_args[i], &j, q_dom);

// 						// if (!tmp->cmd_args[i] || !tmp->cmd_args[i][0])
// 						// 	tmp->cmd_args[i] = NULL;
// 						if (clean)
// 							free(clean);
// 						q_dom = 0;
// 					}
// 					// else
// 					j++;
// 					// printf("it was %c\n", tmp->cmd_args[i][j]);

// 					// j++;
// 					// printf("it is %c\n", tmp->cmd_args[i][j]);

// 					if (!tmp->cmd_args[i] || !tmp->cmd_args[i][j])
// 					// if (!tmp->cmd_args[i][j])
// 						break ;
					
// 				}
// 				i++;
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }


//or >

int	mng_quotes(t_mini *mini)
{
	t_token	*tmp;
	int	i;
	int j;
	char	q_dom;
	// char	*ext;
	char	*clean;

	tmp = mini->tokens;
	// printf("MANAGE QUOTES\n");
	q_dom = 0;

	while (tmp)
	{
		i = 0;
		j = 0;

		q_dom = 0;
		if (tmp->cmd_args)
		{

		
			while(tmp->cmd_args[i])
			{
				j = 0;
				// if (tmp->cmd_args[i][j])
				// {
				// 	if (tmp->cmd_args[i][j] == '\"' || tmp->cmd_args[i][j] == '\'' && !q_dom)
				// 	{
				// 		q_dom = tmp->cmd_args[i][j];
				// 		clean = tmp->cmd_args[i];
				// 		tmp->cmd_args[i] = ft_remove_q(tmp->cmd_args[i], &j, q_dom);
				// 		if (clean)
				// 			free(clean);						
				// 		j++;

				// 	}
				// }

				while(tmp->cmd_args[i][j])
				{


					// printf("before if %c\n", q_dom);
					if (q_dom && tmp->cmd_args[i][j] == q_dom)
					{
						clean = tmp->cmd_args[i];
						tmp->cmd_args[i] = ft_remove(tmp->cmd_args[i], &j, q_dom);
						// if (!tmp->cmd_args[i] || !tmp->cmd_args[i][0])
						// 	tmp->cmd_args[i] = NULL;
						if (clean)
							free(clean);
						q_dom = 0;
						// j++;

					}
					else if((tmp->cmd_args[i][j] == '\"' || tmp->cmd_args[i][j] == '\'') && !q_dom)
					{
						// printf("ENTERED if\n");

						q_dom = tmp->cmd_args[i][j];
						clean = tmp->cmd_args[i];
						tmp->cmd_args[i] = ft_remove(tmp->cmd_args[i], &j, q_dom);
						free(clean);
						// j++;
						// printf("here %c\n", q_dom);
					}
					else if(q_dom && tmp->cmd_args[i][j] == q_dom)
					{
						clean = tmp->cmd_args[i];
						tmp->cmd_args[i] = ft_remove(tmp->cmd_args[i], &j, q_dom);
						// if (!tmp->cmd_args[i] || !tmp->cmd_args[i][0])
						// 	tmp->cmd_args[i] = NULL;
						if (clean)
							free(clean);
						q_dom = 0;
						j++;
					}
					// printf("it was %c\n", tmp->cmd_args[i][j]);

					j++;
					// printf("it is %c\n", tmp->cmd_args[i][j]);

					if (!tmp->cmd_args[i] || !tmp->cmd_args[i][j])
					// if (!tmp->cmd_args[i][j])
						break ;
					
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}






int	quotes(t_mini *mini, t_token *tmp)
{
	char	q_dom;
	// t_token	*tmp;
	int		i;
	int		j;
	bool	dom_closed;
	bool	dom_opened;	

	q_dom = 0;
	// tmp = mini->tokens;
	dom_closed = false;
	dom_opened = false;
	i = 0;
	j = 0;
	// printf("in quotes\n");
	if(tmp->cmd_args && tmp->type != 'd')
	{

	
		while(tmp->cmd_args[i])
		{
			j = 0;
			// printf("entered i_\n");

			while (tmp->cmd_args[i][j])
			{
				// printf("entered ij\n");
				// printf("qdom %c\n", q_dom);
				// printf("arg num is %i %s\n", i, tmp->cmd_args[i]);
				// printf("j is %i\n", j);
				// printf("hehe char is %d\n", tmp->cmd_args[i][j]);

				while (tmp->cmd_args[i][j] && (!dom_opened && !dom_closed) || (dom_closed && dom_opened) && q_dom == 0)
				{
					// printf("closed %i\n", dom_closed);
	// 				printf("opened %i\n", dom_opened);
					if (tmp->cmd_args[i][j] == '\"' || tmp->cmd_args[i][j] == '\'')
					{
						if (dom_closed && dom_opened)
						{
							// printf("entered IF\n");
							// printf("THAT char is %c\n", tmp->cmd_args[i][j]);
							q_dom = tmp->cmd_args[i][j];
							dom_closed = false;
							// printf("1 %c is the q \n", tmp->cmd_args[i][j]);
							j++;
							break ;
						}
						else if (!dom_opened && !dom_closed)
						{
							// printf("2 %c is the q \n", tmp->cmd_args[i][j]);

							q_dom = tmp->cmd_args[i][j];
							dom_opened = true;
							dom_closed = false;
							j++;
							break ;
						}
					}
					j++;
					if (!tmp->cmd_args[i][j])
						break ;

				}
				while (tmp->cmd_args[i][j] && (dom_opened == true && !dom_closed))
				{
					if (tmp->cmd_args[i][j] == q_dom)
					{
						// printf("compr %c %c \n", tmp->cmd_args[i][j], q_dom);

						dom_closed = true;
						q_dom = 0;
						j++;
						break ;
					}
					j++;
				}
			}
			i++;
		}
	}
	if (dom_closed && dom_opened)
	{
		// if (q_dom == '\"' || !q_dom)
		// 	check_env_vr(mini);			
		// remove_q(mini, q_dom);
		// printf("3 %c is the q \n", q_dom);
		return(0);
		// printf(">> quotes pass\n");
	}
	else if (!dom_closed && !dom_opened)
	{
		// check_env_vr(mini);	
		// printf(">> no quotes \n");
		return (0);
	
	}
	else 
	{
		// printf(">> ERROR: quote syntax\n");
		return (1);
	}
	// tmp = tmp->next;
	
	// printf("q DONE \n");
	return (0);
}