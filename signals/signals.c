/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:51:20 by obibby            #+#    #+#             */
/*   Updated: 2022/09/21 14:12:03 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_quit(int sig)
{
	(void)sig;
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	rl_pending_input = 0;
}

void	sig_int(int	sig)
{
	(void)sig;
	kill(0, SIGQUIT);
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}
