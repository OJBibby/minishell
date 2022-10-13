/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:42:48 by obibby            #+#    #+#             */
/*   Updated: 2022/10/13 19:58:22 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

int print_exported(t_env *env, int fd)
{
	t_env *temp;

	temp = env;
	while (temp)
	{
		write(fd, "declare -x ", 11);
		write(fd, temp->str, ft_strlen(temp->str));
		write(fd, "\n", 1);
		temp = temp->next;
	}
	return (0);
}

int ft_unset(t_info *info)
{
	t_token *token;
	t_env *delete;
	t_env *env;
	int i;

	token = info->token;
	i = 0;
	while (token->cmd_args[++i])
	{
		delete = find_env_node(info->env_ll, token->cmd_args[i], 0);
		if (!delete)
			return (1);
		if (!delete->prev && delete->next)
			info->env_ll = delete->next;
		if (!delete->prev && !delete->next)
			info->env_ll = NULL;
		if (delete->prev)
			delete->prev->next = delete->next;
		if (delete->next)
			delete->next->prev = delete->prev;
		if (delete->str)
			free(delete->str);
		free(delete);
	}
	return (0);
}

int check_export(char *str)
{
	int	j;

	if ((str[0] == '=') || ((str[0] < 'A' || str[0] > 'Z') && (str[0] < 'a' || str[0] > 'z')))
	{
		printf("minishell: export: %s: not a valid identifier.\n", str);
		return (1);
	}
	j = 0;
	while (str[j])
	{
		if (str[j++] == '=')
			break;
		if (!str[j])
			return (1);
	}
	return (0);
}

int ft_export(t_info *info)
{
	t_env *env;
	int fd;
	int i;
	int j;

	fd = set_fd(info->token, info);
	if (!info->token->cmd_args[1])
		return (print_exported(info->env_ll, fd));
	i = 0;
	while (info->token->cmd_args[++i])
	{
		if (check_export(info->token->cmd_args[i]))
			continue ;
		env = find_env_node(info->env_ll, info->token->cmd_args[i], 1);
		if (!env)
		{
			env = add_env_node(info);
			if (!env)
				return (error_return(0, NULL, "Memory allocation fail."));
		}
		if (add_env_var(info->token->cmd_args[i], env) == -1)
			return (error_return(0, NULL, "Memory allocation fail."));
	}
	return (0);
}
