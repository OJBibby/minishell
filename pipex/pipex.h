/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:51:34 by obibby            #+#    #+#             */
/*   Updated: 2022/09/19 15:14:54 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <sys/wait.h>
# include "../minishell.h"

typedef struct	s_info {
	char	*buffer;
	int		stdout_fd;
	int		stdin_fd;
	int		infile_no;
	int		outfile_no;
	int		out_now;
	int		in_now;
	int		pipe_fd[2];
	int		total_ops;
	int		done_ops;
	char	**env;
	t_env	*env_ll;
	t_token	*token;
}	t_info;

typedef struct	s_cmd {
	char	**cmds;
	char	*prog;
	int		total;
	t_info	*info;
}	t_cmd;

int	error_return(int id, void *mem, char *str);
int ft_echo(t_token *token, t_info *info);
int	ft_pwd(t_token *token, t_info *info);
int	ft_cd(t_token *token, t_info *info);
int	exit_shell(t_mini *mini);
int	ft_env(t_token *token, t_info *info);
void	*ft_calloc(size_t elenum, size_t size);
int	exec_cmds(t_token *token, t_info *info);

#endif
