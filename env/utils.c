/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:34:31 by obibby            #+#    #+#             */
/*   Updated: 2022/09/21 10:35:23 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

int	revert_list(t_env *tmp, int i)
{
	while (--i > 0)
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

t_env	*get_last_node(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
