/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:43:09 by cgreenpo          #+#    #+#             */
/*   Updated: 2023/02/01 09:39:55 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'));
}

int	ft_isupper(int c)
{
	return ((c >= 'A' && c <= 'Z'));
}

int	ft_islower(int c)
{
	return ((c >= 'a' && c <= 'z'));
}

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}
