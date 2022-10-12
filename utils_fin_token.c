#include "minishell.h"

int	mng_token_list(t_util *ut)
{	
	t_token	*new;

	new = init_token();
	if (!ut->ret)
	{
		ut->ret = new;
		ut->head = new;
	}
	else
	{
		new->prev = ut->ret;
		ut->ret->next = new;
		ut->ret = ut->ret->next;
	}
	if (ut->ret->prev)
	{
		if (!ut->ret->prev->output)
		{
			free_token_light(ut->ret);//!!!!!
			return (1);
		}
		ut->ret->input = put_pipe();
	}
	return (0);
}

char	**put_pipe(void)
{
	char	**str;

	str = malloc(sizeof(char) * 2);
	str[0] = ft_strdup("|");
	str[1] = 0;
	return (str);
}

void	init_var(t_util *ut, int *i, int *j, t_mini *mini)
{
	*i = 0;
	*j = 0;
	ut->old = mini->tokens;
	ut->ret = NULL;
}
