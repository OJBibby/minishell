/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgreenpo <cgreenpo@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:41:31 by cgreenpo          #+#    #+#             */
/*   Updated: 2022/08/13 17:40:03 by cgreenpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include "minishell.h"


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
	// printf("k is%i\n", k);

	return (k);
}

static char	*ft_wordmem(const char *str, char c, int *j)
{
	int		i;
	char	*word;
	// int		j;

	i = 0;
	// j = 0;
	while (str[i] && str[i] != c)
		i++;
	while (str[i] == c)
		i++;
	while (str[i] && str[i] != c)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	while (i--)
	{
		word[*j] = str[*j];
		(*j)++;
	}
	word[*j] = '\0';
	// str += j;
	// printf("after split %s\n", str);
	return (word);
}

char	**ft_split(char *s, char c, t_mini *mini, t_token *token)
{
	char	**split;
	int		counter;
	int		i;
	int		j;


	i = 0;
	if (!s)
		return (NULL);
	s = get_cmd_name(mini, s, token);
	counter = ft_words_c(s, c);
	counter++;
	split = malloc(sizeof(char *) * (counter + 1));
	if (!split)
		return (NULL);
	split[0] = token->cmd_name;
	i = 1;
	while (i < counter)
	{
		// while (*s && *s == c)
		// 	s++;
		j = 0;

		split[i] = ft_wordmem(s, c, &j);
		if (!split[i])
			free_words(i, split);
		s += j;
		// while (*s && *s != c)
		// 	s++;
		i++;
	}
	split[i] = 0;
	return (split);
}
