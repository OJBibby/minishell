/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:51:20 by obibby            #+#    #+#             */
/*   Updated: 2023/02/01 09:37:30 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sig_quit(int sig)
{
	g_status.exit_status = 128 + sig;
}

void	sig_int(int sig)
{
	if (g_status.pid != 0)
	{
		kill(g_status.pid, SIGINT);
		write(1, "\n", 1);
	}
	else
	{
		rl_replace_line("", 1);
		write(1, "^C\n", 3);
		rl_on_new_line();
		rl_redisplay();
	}
	g_status.exit_status = 128 + sig;
}
