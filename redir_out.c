#include "minishell.h"

int	out_condition_three(t_util *ut, int *i, int *j)
{
	if (check_valid_args(ut))
		return (1);
	ut->ret->output = add_string(ut->ret->output, ut->old->next->cmd_args[0]);
	mod_append(ut, 1);
	if (ut->old->next->cmd_args[1])
		ut->ret->cmd_args = copy_args(ut->old->next->cmd_args, 1);
	// if (ut->old->next->type == '|')
	// 	ut->ret->output = add_string(ut->ret->output, "|");
	return (0);
}

int	out_condition_two(t_util *ut, int *i, int *j)
{
	char	**tmp_arr;
	int		ct;

	*i = 0;
	if (check_valid_args(ut))
		return (1);
	// if (ut->old->next->cmd_args[1])
	// {
	// 	tmp_arr = ut->ret->cmd_args;
	// 	ut->ret->cmd_args = copy_args(ut->old->next->cmd_args, 1);
	// 	if (tmp_arr)
	// 		free_d_arr(tmp_arr);
	// }
	ut->ret->output = add_string(ut->ret->output, ut->old->next->cmd_args[0]);

	if (ut->old->next->cmd_args[1])
	{
		ct = 1;
		while (ut->old->next->cmd_args[ct])
		{
			ut->ret->cmd_args = add_string(ut->ret->cmd_args, ut->old->next->cmd_args[ct]);
			ct++;
		}
	}

	mod_append(ut, 1);
	return (0);
}

int	out_condition_one(t_util *ut, int *i, int *j)
{
	char	**tmp_arr;
	int		ct;

	tmp_arr = ut->ret->cmd_args;
	ut->ret->cmd_args = copy_args(ut->old->cmd_args, 0);
	if (tmp_arr)
		free_d_arr(tmp_arr);
	if (check_valid_args(ut))
		return (1);
	// tmp_arr = copy_args(ut->old->next->cmd_args, 0);
	if (ut->ret->output)
		free_d_arr(ut->ret->output);
	// ut->ret->output = tmp_arr;
	ut->ret->output = add_string(ut->ret->output, ut->old->next->cmd_args[0]);
	if (ut->old->next->cmd_args[1])
	{
		ct = 1;
		while (ut->old->next->cmd_args[ct])
		{
			ut->ret->cmd_args = add_string(ut->ret->cmd_args, ut->old->next->cmd_args[ct]);
			ct++;
		}
	}

	*i = 0;
	*j = ut->olen;
	while (ut->ret->output[*j])
	{
		(*j)++;
		(*i)++;
	}
	mod_append(ut, *i);
	return (0);
}

int	redir_out(t_util *ut, int *i, int *j)
{
	char	**tmp_arr;
	int		*tmp_int;

	if (ut->old->cmd_args && ut->old->cmd_args[0] && ut->old->cmd_args[0][0])
	{
		if ((ut->old->prev && ut->old->prev->type == '|') || !ut->old->prev)
		{
			if (out_condition_one(ut, i, j))
				return (1);
		}
		else if (ut->old->prev->type == '>' || ut->old->prev->type == '<'
			|| ut->old->prev->type == 'a' || ut->old->prev->type == 'd')
		{
			if (out_condition_two(ut, i, j))
				return (1);
		}
		// if (ut->old->next->type == '|')
		// 	ut->ret->output = add_string(ut->ret->output, "|");
	}
	else
	{
		if (out_condition_three(ut, i, j))
			return (1);
	}
	if (ut->old->next->type == '|')
		ut->ret->output = add_string(ut->ret->output, "|");
	return (0);
}
