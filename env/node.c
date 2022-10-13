/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:01:23 by obibby            #+#    #+#             */
/*   Updated: 2022/10/13 22:02:16 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

t_env	*find_env_node(t_env *env, char *str, int mode)
{
	t_env	*tmp;
	t_env	*prev;
	int		len;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->str, str, i + mode))
			if (mode == 1 || (mode == 0 && !str[i] && tmp->str[i] == '='))
				return (tmp);
		prev = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

t_env	*add_env_node(t_info *info)
{
	t_env	*env;
	t_env	*prev;

	env = info->env_ll;
	while (env)
	{
		prev = env;
		env = env->next;
	}
	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	env->prev = prev;
	prev->next = env;
	env->str = NULL;
	env->next = NULL;
	return (env);
}
