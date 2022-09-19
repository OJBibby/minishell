/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgreenpo <cgreenpo@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:43:09 by cgreenpo          #+#    #+#             */
/*   Updated: 2022/08/23 12:31:27 by cgreenpo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"
#include "minishell.h"


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

