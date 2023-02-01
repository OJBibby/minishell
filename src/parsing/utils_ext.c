/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgreenpo <cgreenpo@student.42wolfsburg.de> +#+  +:+       +#+    	  */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:43:46 by cgreenpo            #+#    #+#           */
/*   Updated: 2022/10/14 12:30:24 by cgreenpo           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*extract(char *str, int start, int n)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (str[i])
		i++;
	ret = malloc(sizeof(char) * (i - n + 1));
	i = 0;
	j = 0;
	while (str[i] && i < start)
		ret[j++] = str[i++];
	if (i == start)
	{
		while (str[i] && n--)
			i++;
	}
	while (str[i])
	{
		ret[j] = str[i];
		j++;
		i++;
	}
	ret[j] = 0;
	return (ret);
}

t_env	*get_env_node(t_env *env, char *var)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->str, var, ft_strlen(var)) == 0)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_env_str(t_env *env, char *var)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp_mod(tmp->str, var, ft_strlen(var)) == 0)
		{
			return (tmp->str);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*ft_insert(char *s1, char *point_of_in, int remove, int index)
{
	int		i;
	char	*ret;
	char	*tail;
	int		found;
	char	*clean;

	remove++;
	i = 0;
	found = 0;
	clean = 0;
	ret = ft_strndup(s1, index);
	point_of_in += remove;
	clean = ret;
	ret = ft_strjoin(ret, point_of_in);
	if (clean)
		free(clean);
	return (ret);
}
