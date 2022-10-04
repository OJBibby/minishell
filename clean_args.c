#include "minishell.h"

char	**remove_empty(char **or, int *n)
{
	int	i;
	int	j;
	char	**ret;

	i = 0;
	j = 0;
	// printf("old arg = %s\n", or[*n]);

	while(or[i])
		i++;
	// printf("i = %i\n", i);

	ret = malloc(sizeof(char *) * i);

	ret[--i] = 0;
	// printf("n = %i\n", *n);

	i = 0;
	// printf("old arg = %s\n", or[*n]);

	while(or[i])
	{
		if (i == *n)
			i++;
		else
		{
			ret[j] = ft_strdup(or[i]);
			// printf("-- old arg %s \n", or[i]);

			// printf("-- new arg %s \n", ret[j]);
			j++;
			i++;
		}
	
	}
	(*n)--;
	// printf("n = %i\n", *n);
	i = 0;
	while (ret[i])
	{
		// printf("new arg = %s\n", ret[i]);
		i++;

	}

	return (ret);
}

void	clean_args(t_token *token)
{
	t_token *tmp;
	int		i;
	int		j;
	char	**clean;

	tmp = token;


	while(tmp)
	{
		i = 0;
		while(tmp->cmd_args && tmp->cmd_args[i])
		{
			j = 0;
			// while (tmp->cmd_args[j])
			// 	j++;
			// if (i < j && !tmp->cmd_args[i][0])
			// if (tmp->cmd_args[i])
			if(tmp->cmd_args[i])
			{
				// printf("tmp->cmd_args[i] = %s\n", tmp->cmd_args[i]);

				if (!tmp->cmd_args[i][0])
				{
					// printf("empty \n");

					clean = tmp->cmd_args;
					tmp->cmd_args = remove_empty(tmp->cmd_args, &i);
					
					free_d_arr(clean);
					// printf("leaving empty \n");

				}
			}
			else
			{
				i++;
				if (!tmp->cmd_args[i])
					break ;
			}
			i++;
		}
		tmp = tmp->next;
	}
}