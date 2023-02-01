/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgreenpo <cgreenpo@student.42wolfsburg.de> +#+  +:+       +#+    	  */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 22:43:46 by cgreenpo            #+#    #+#           */
/*   Updated: 2022/10/14 12:30:24 by cgreenpo           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_builtin(char **args)
{
	if (!args[0])
		return (-1);
	if (!ft_strncmp_p(args[0], "export", 6))
		return (1);
	else if (!ft_strncmp_p(args[0], "unset", 5))
		return (1);
	else if (!ft_strncmp_p(args[0], "echo", 4))
		return (1);
	else if (!ft_strncmp_p(args[0], "cd", 2))
		return (1);
	else if (!ft_strncmp_p(args[0], "pwd", 3))
		return (1);
	else if (!ft_strncmp_p(args[0], "env", 3))
		return (1);
	else if (!ft_strncmp_p(args[0], "exit", 4))
		return (1);
	return (0);
}

int	check_local_adress(t_token *token, char	*adress, t_mini *mini)
{
	if (access(adress, F_OK) == 0)
	{
		token->path = ft_strdup(adress);
		return (0);
	}
	return (1);
}

int	an_exit(char **adress, int i, t_token *token)
{
	if (access(adress[i], F_OK) == 0)
	{
		token->path = ft_strdup(adress[i]);
		free_d_arr(adress);
		return (0);
	}
	else
	{
		return (1);
	}
}

int	iter_path(char **adress, char *str, t_token *token, t_mini *mini)
{
	int		i;
	char	*clean;

	i = 0;
	clean = NULL;
	while (adress[i])
	{
		clean = adress[i];
		adress[i] = ft_strjoin(adress[i], "/");
		free(clean);
		clean = adress[i];
		adress[i] = ft_strjoin(adress[i], str);
		free(clean);
		if (!an_exit(adress, i, token))
			return (0);
		i++;
	}
	return (1);
}

int	check_path(t_mini *mini, t_token *token)
{
	char	**adress;
	int		i;
	char	*clean;
	char	*tmp_adr;

	if (ft_strchr(token->cmd_args[0], '/'))
		return (check_local_adress(token, token->cmd_args[0], mini));
	tmp_adr = get_env_str(mini->env, "PATH");
	if (tmp_adr)
		tmp_adr += 5;
	else if (!tmp_adr)
		return (1);
	adress = ft_split_or(tmp_adr, ':');
	i = 0;
	clean = 0;
	if (!iter_path(adress, token->cmd_args[0], token, mini))
		return (0);
	else
	{
		free_d_arr(adress);
		token->path = NULL;
		return (1);
	}
}
