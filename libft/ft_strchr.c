/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:18:50 by cgreenpo          #+#    #+#             */
/*   Updated: 2022/09/21 15:46:15 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	while ((char)c != *s && *s)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

int	ft_strchr_nb(const char *s, int c)
{
	int	i;

	i = 0;
	while ((char)c != *s && *s)
	{
		i++;
		s++;
	}
	if (*s == (char)c)
		return (i);
	return (-1);
}
