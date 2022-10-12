#include "minishell.h"

int	in_condition_three(t_util *ut, int *i, int *j)
{
	char	**tmp_arr;

	if (check_valid_args(ut))
		return (1);
	if (ut->ret->input)
		free_d_arr(ut->ret->input);
	ut->ret->input = NULL;
	ut->ret->input = add_string(ut->ret->input, ut->old->next->cmd_args[0]);
	mod_heredoc(ut, 1);
	if (ut->old->next->cmd_args[1])
		ut->ret->cmd_args = copy_args(ut->old->next->cmd_args, 1);
	return (0);
}

void	in_condition_two(t_util *ut, int *i, int *j)
{
	char	**tmp_arr;

	*i = 0;
	while (ut->old && ut->old->next && ut->old->next->cmd_args
		&& ut->old->next->cmd_args[*i])
	{
		tmp_arr = add_string(ut->ret->input, ut->old->next->cmd_args[*i]);
		ut->ret->input = tmp_arr;
		(*i)++;
		mod_heredoc(ut, 1);
	}
}

int	in_condition_one(t_util *ut, int *i, int *j)
{
	char	**tmp_arr;

	tmp_arr = ut->ret->cmd_args;
	ut->ret->cmd_args = copy_args(ut->old->cmd_args, 0);
	if (tmp_arr)
		free(tmp_arr);
	tmp_arr = ut->ret->input;
	if (ut->old->next->cmd_args)
		ut->ret->input = copy_args(ut->old->next->cmd_args, 0);
	else
		return (1);
	if (tmp_arr)
		free_d_arr(tmp_arr);
	*i = 0;
	*j = ut->ilen;
	while (ut->ret->input[(*j)++])
		(*i)++;
	mod_heredoc(ut, *i);
	return (0);
}

int	redir_in(t_util *ut, int *i, int *j)
{
	char	**tmp_arr;
	int		*tmp_int;

	if (ut->old->cmd_args && ut->old->cmd_args[0] && ut->old->cmd_args[0][0])
	{
		if ((ut->old->prev && ut->old->prev->type != '<'
				&& ut->old->prev->type != '>' && ut->old->prev->type != 'd'
				&& ut->old->prev->type != 'a') || !ut->old->prev)
		{
			if (in_condition_one(ut, i, j))
				return (1);
		}
		else if (ut->old->prev->type == '<' || ut->old->prev->type == '>'
			|| ut->old->prev->type == 'd' || ut->old->prev->type == 'a')
			in_condition_two(ut, i, j);
	}
	else
	{
		if (in_condition_three(ut, i, j))
			return (1);
	}
	if (ut->old->next->type == '|')
		ut->ret->output = add_string(ut->ret->output, "|");
	return (0);
}
