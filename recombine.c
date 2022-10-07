#include "minishell.h"

void	recombine(t_token *tokens)
{
	t_token		*token;
	int			i;
	int			j;

	token = tokens;
	i = 0;

	while (tokens)
	{
		while (token->cmd_args && token->cmd_args[i])
		{
			j = 0;
			if (token->cmd_args[i + 1])
			{
				if ()
			}

		}
	}

}