/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 23:37:12 by obibby            #+#    #+#             */
/*   Updated: 2022/09/21 09:37:00 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

int	ft_cd(t_token *token, t_info *info)
{
	close(info->out_now);
	close(info->in_now);
	if (!token->output && chdir(token->cmd_args[1]))
	{
		printf("Error changing directory.\n");
		return (1);
	}
	return (2);
}
