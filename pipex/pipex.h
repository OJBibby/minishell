/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:51:34 by obibby            #+#    #+#             */
/*   Updated: 2022/09/15 13:43:06 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <sys/wait.h>

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
//# include "../minishell.h"

typedef struct	s_token {
		struct s_token *next;
		char **args;
		char *input;
		char *output;
		int  heredoc[1];
		int  append[1];
} t_token;

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
//int	exit_shell(t_mini *mini);

void	*ft_calloc(size_t elenum, size_t size);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin_slash(char const *s1, char const *s2);
char	**ft_split_or(char const *s, char c);

#endif
