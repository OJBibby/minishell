/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_or.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:41:31 by cgreenpo          #+#    #+#             */
/*   Updated: 2023/02/01 09:40:01 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_words(int i, char **tab)
{
	while (i > 0)
	{
		free(tab[i - 1]);
		i--;
	}
	free(tab);
}

static int	ft_words_c(const char *str, char c)
{
	int	k;
	int	n;
	int	s_point;

	k = 0;
	n = 0;
	s_point = 0;
	if (!str)
		return (0);
	while (str[n])
	{
		if (str[n] != c && s_point == 0)
		{
			s_point = 1;
			k++;
		}
		else if (str[n] == c)
			s_point = 0;
		n++;
	}
	return (k);
}

static char	*ft_wordmem(const char *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split_or(char const *s, char c)
{
	char	**split;
	int		counter;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	counter = ft_words_c(s, c);
	split = malloc(sizeof(char *) * (counter + 1));
	if (!split)
		return (NULL);
	while (i < counter)
	{
		while (*s && *s == c)
			s++;
		split[i] = ft_wordmem(s, c);
		if (!split[i])
			free_words(i, split);
		while (*s && *s != c)
			s++;
		i++;
	}
	split[i] = 0;
	return (split);
}
