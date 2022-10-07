#include "minishell.h"

char	*ft_remove_q(char *str, int *j, char c)

{
	// ^^^^^MEMORY
	int	i;
	char	*ret;
	char	*tmp;
	int		stop;

	i = 0;
	stop = 0;
	ret = malloc(sizeof(char) * ft_strlen(str));
	while (str[i])
	{
		if (str[i] == c && !stop)
		{
			str++;
			stop = 1;
		}
		else
		{
			ret[i] = str[i];
			i++;
		}
	}
	ret[i] = 0;
	// (*j)--;
	printf("____after q removing{%sEND\n", ret);
	return (ret);


}

char	*ft_remove(char *str, int *j, char c)

{
	// ^^^^^MEMORY
	int	i;
	char	*ret;
	char	*tmp;
	int		n;

	i = 0;
	n = 0;
	ret = malloc(sizeof(char) * ft_strlen(str));
	while (str[n])
	{
		if (n != *j)
		{
			ret[i] = str[n];
			i++;
			n++;
		}
		else
			n++;
	}
	ret[i] = 0;
	(*j)--;
	// printf("____after removing{%sEND\n", ret);
	return (ret);


}


int	mng_spaces(t_mini *mini)
{
	t_token	*tmp;
	int	i;
	int j;
	int	stop;
	char	q_dom;
	char	*s;
	int		n;
	char	*ext;
	int		index;
	bool	alt;
	char	*clean;

	// printf("in mng_spaces\n");

	stop = -1;
	tmp = mini->tokens;
	alt = false;
	// printf("MANAGE SPACES\n");
	while (tmp)
	{
		i = 0;
		j = 0;

		q_dom = 0;
		// if (tmp->cmd_args && tmp->cmd_args[0])
		if (tmp->cmd_args)
		{

		
			while(tmp->cmd_args[i])
			{
				j = 0;
				// q_dom = 0;

				while(tmp->cmd_args[i][j])
				{
					n = 0;
					if((tmp->cmd_args[i][j] == '\"' || tmp->cmd_args[i][j] == '\'') && !q_dom)
					{
						// printf("opt 1\n");
						// if (!q_dom)
						q_dom = tmp->cmd_args[i][j];
						// j++;
						// printf("here %c\n", q_dom);
						// printf("arg %s\n", tmp->cmd_args[i]);

					}
					else if(q_dom && (tmp->cmd_args[i][j] == q_dom))
					{
						// printf("opt 2\n");
						// printf("here %c\n", tmp->cmd_args[i][j]);
						q_dom = 0;
						// j++;
					}
					else if ((tmp->cmd_args[i][j] == ' ') && !q_dom)
					{
						// printf("opt 3\n");

						free(tmp->cmd_args[i]);
						clean = ft_remove(tmp->cmd_args[i], &j, ' ');
						tmp->cmd_args[i] = clean;
						// j++;
					}
					j++;
				}
				i++;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
