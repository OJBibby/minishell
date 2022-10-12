#include "minishell.h"

int	i_got_no_type(t_util *ut, t_mini *mini)
{
	if (ut->old->prev && (ut->old->prev->type == '<'
			|| ut->old->prev->type == '>' || ut->old->prev->type == 'a'
			|| ut->old->prev->type == 'd'))
	{
		free_token(mini);
		mini->tokens = ut->head;
		return (-1);
	}
	free_d_arr(ut->ret->cmd_args);
	if (ut->old->cmd_args)
		ut->ret->cmd_args = copy_args(ut->old->cmd_args, 0);
	free_token(mini);
	mini->tokens = ut->head;
	return (-1);
}

int	type_pipe(t_util *ut, int *i, int *j)
{
	char	**tmp_arr;
	int		*tmp_int;

	if (!ut->old->cmd_args || !ut->old->cmd_args[0]
		|| !ut->old->cmd_args[0][0] || !ut->old->next)
	{
		free_token_light(ut->head);
		return (1);
	}
	if ((ut->old->prev && ut->old->prev->type == '|') || !ut->old->prev)
	{
		ut->ret->cmd_args = copy_args(ut->old->cmd_args, 0);
		ut->ret->output = put_pipe();
		ut->old = ut->old->next;
	}
	else if (ut->old->prev && ut->old->prev->type != '|')
		ut->old = ut->old->next;
	return (0);
}

int	not_pipe(t_util *ut, int *i, int *j, t_mini *mini)
{
	if (ut->old->type == '<' || ut->old->type == 'd')
	{
		if (redir_in(ut, i, j))
			return (1);
	}
	else if (ut->old->type == '>' || ut->old->type == 'a')
	{
		if (redir_out(ut, i, j))
			return (1);
	}
	else if (!ut->old->type && !ut->old->next)
		return (i_got_no_type(ut, mini));
	else
	{
		free_token_light(ut->head);
		return (1);
	}
	ut->old = ut->old->next;
	return (0);
}

int	check_pipe_type(t_util *ut, int *i, int *j)
{
	if (ut->old->type == '|')
	{
		if (type_pipe(ut, i, j))
			return (1);
	}
	return (0);
}

int	fin_token(t_mini *mini)
{
	int		i;
	int		j;
	t_util	ut;

	init_var(&ut, &i, &j, mini);
	while (ut.old)
	{
		if (mng_token_list(&ut))
			return (1);
		ut.olen = 0;
		ut.ilen = 0;
		while (ut.old->type != '|' && ut.old)
		{
			ut.exit = not_pipe(&ut, &i, &j, mini);
			if (ut.exit == 1)
				return (1);
			else if (ut.exit == -1)
				return (0);
		}
		if (check_pipe_type(&ut, &i, &j))
			return (1);
	}
	return (0);
}
