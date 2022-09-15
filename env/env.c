/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:21:45 by obibby            #+#    #+#             */
/*   Updated: 2022/09/15 14:54:11 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex/pipex.h"

int	revert_list(t_env *tmp, int i)
{
	while (i-- > 0)
	{
		free(tmp->str);
		tmp = tmp->prev;
		free(tmp->next);
		tmp->next = NULL;
	}
	return (0);
}

int	shift_args(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i])
	{
		free(args[i - 1]);
		args[i - 1] = ft_calloc(ft_strlen(args[i]) + 1, sizeof(char));
		if (!args[i - 1])
			return (1);
		j = -1;
		while (args[i][++j])
			args[i - 1][j] = args[i][j];
		args[i - 1][j] = '\0';
	}
	free(args[i - 1]);
	args[i - 1] = ft_calloc(1, sizeof(char));
	if (!args[i - 1])
		return (1);
	args[i - 1] = NULL;
	free(args[i]);
	return (0);
}

int	ft_env(t_token *token, t_info *info)
{
	int	i;
	int	j;
	int	fd;
	int	retval;
	char	*tmp_env;
	char	*saved_env;
	t_env	*tmp;

	fd = 1;
	if (info->outfile_no)
		fd = info->outfile_no;
	else if (token->output)
		fd = info->out_now;
	tmp = info->env_ll;
	while (tmp->next)
		tmp = info->env_ll;
	i = 0;
	while (token->args[++i])
	{
		j = -1;
		while (token->args[i][++j])
		{
			if (token->args[i][j] == '=')
			{
				tmp->next = malloc(sizeof(t_env));
				tmp->next->prev = tmp;
				tmp = tmp->next;
				tmp->str = ft_strdup(token->args[i]);
				tmp->next = NULL;
				break ;
			}
		}
		if (!token->args[i][j])
			break ;
	}
	tmp_env = list_to_arr(info);
	if (!token->args[i])
	{
		j = 0;
		while (tmp_env[j])
			write(fd, &tmp_env[j++], 1);
		free(tmp_env);
		revert_list(tmp, i);
		return (0);
	}
	shift_args(token->args);
	saved_env = info->env;
	info->env = tmp_env;
	retval = exec_cmds(token, info);
	info->env = saved_env;
	free(tmp_env);
	revert_list(tmp, i);
	return (retval);
}
