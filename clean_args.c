#include "minishell.h"

char	**remove_empty(char **or, int *n)
{
	int		i;
	int		j;
	char	**ret;

	i = 0;
	j = 0;
	while (or[i])
		i++;
	ret = malloc(sizeof(char *) * i);
	ret[--i] = NULL;
	i = 0;
	while (or[i])
	{
		if (i == *n)
			i++;
		else
			ret[j++] = ft_strdup(or[i++]);
	}
	(*n)--;
	i = 0;
	while (ret[i])
		i++;
	return (ret);
}

void	check_empty(int *i, t_token *tmp)
{
	char	**clean;

	if (!tmp->cmd_args[*i][0])
	{
		clean = tmp->cmd_args;
		tmp->cmd_args = remove_empty(tmp->cmd_args, i);
		if (clean)
			free_d_arr(clean);
		
	}
}

void	clean_args(t_token *token)
{
	t_token	*tmp;
	int		i;
	int		j;

	tmp = token;
	while (tmp)
	{
		i = 0;
		while (tmp->cmd_args && tmp->cmd_args[i])
		{
			j = 0;
			if (tmp->cmd_args[i])
				check_empty(&i, tmp);
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
