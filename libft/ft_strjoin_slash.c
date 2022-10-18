/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_slash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 09:41:17 by cgreenpo          #+#    #+#             */
/*   Updated: 2022/09/21 15:46:29 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_slash(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[n++] = s1[i++];
	}
	str[n++] = '/';
	i = 0;
	while (s2[i])
	{
		str[n++] = s2[i++];
	}
	str[n] = '\0';
	return (str);
}
