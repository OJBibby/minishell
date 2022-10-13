/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:50:37 by obibby            #+#    #+#             */
/*   Updated: 2022/10/13 16:28:02 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

char	**list_to_arr(t_env *env)
{
	t_env	*tmp;
	int		i;
	char	**ret;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	ret = ft_calloc((i + 1), sizeof(char **));
	if (!ret)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		ret[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
