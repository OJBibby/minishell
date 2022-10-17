/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:44:23 by cgreenpo          #+#    #+#             */
/*   Updated: 2022/09/23 10:36:50 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_ntoch(int nb, char *s, size_t *i)
{
	if (nb < 0)
	{
		s[*i] = '-';
		(*i)++;
		ft_ntoch(-nb, s, i);
	}
	else if (nb <= 9)
	{
		s[*i] = (char)(nb + '0');
		(*i)++;
	}
	else
	{
		ft_ntoch(nb / 10, s, i);
		ft_ntoch(nb % 10, s, i);
	}
}

char	*ft_itoa(int n)
{
	size_t	i;
	size_t	sz;
	int		nb;
	char	*s;

	i = 0;
	sz = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nb = n;
	while (nb)
	{
		nb /= 10;
		sz++;
	}
	if (n <= 0)
		sz++;
	s = (char *)malloc((sz + 1) * sizeof(*s));
	if (s == NULL)
		return (NULL);
	ft_ntoch(n, s, &i);
	s[sz] = '\0';
	return (s);
}
