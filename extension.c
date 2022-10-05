#include "minishell.h"


char	*extract(char *str, int start, int n)
{
	int	i;
	int	j;
	char *ret;

	i = 0;
	// printf("start is %i\n", start);
	// start--;
	while(str[i])
		i++;
	ret = malloc(sizeof(char) * (i - n + 1));
	i = 0;
	j = 0;
	while (str[i] && i < start)
	{
		ret[j] = str[i];
		j++;
		i++;
	}
	if (i == start)
	{
		while(str[i] && n--)
			i++;
	}
	while(str[i])
	{
		ret[j] = str[i];
		j++;
		i++;
	}
	ret[j] = 0;

	return(ret);

}


char	**list_to_arr(t_env *env)
{
	t_env	*tmp;
	int		i;
	char	**ret;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	ret = ft_calloc((i + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp)
	{
		ret[i] = ft_strdup(tmp->str);
		tmp = tmp->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	free_env_arr(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (1);
	while(env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	return(0);
}



t_env	*get_env_node(t_env *env, char *var)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	while(tmp)
	{
		if (ft_strncmp(tmp->str, var, ft_strlen(var)) == 0)
		{
			return(tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_env_str(t_env *env, char *var)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	while(tmp)
	{
		if (ft_strncmp_mod(tmp->str, var, ft_strlen(var)) == 0)
		{
			// printf("not fail?");

			return(tmp->str);
		}
		tmp = tmp->next;
	}
	return (NULL);
}


char	*ft_insert(char *s1, char *point_of_in, int remove, int index)
{
	int	i;
	char	*ret;
	char	*tail;
	int		found;
	char	*clean;

	remove++;
	i = 0;
	found = 0;
	// ret = malloc(sizeof(char) * (ft_strlen(s1) -  + ft_strlen(s2)));
	clean = 0;
	ret = strndup(s1, index); //!!!
	// printf("ret %s\n", ret);

	// ret = ft_strjoin(ret, s2); 
	// printf("ret %s\n", ret);

	// printf("point_of_in %s\n", point_of_in);
	point_of_in += remove;
	// printf("point_of_in %s\n", point_of_in);

	// printf("point_of_in %s\n", point_of_in);
	clean = ret;
	ret = ft_strjoin(ret, point_of_in);
	if (clean)
		free(clean);
	return (ret);

}


int	check_env_vr(t_mini *mini)
{
	t_token	*tmp;
	int	i;
	int j;
	char	q_dom;
	char	*s;
	int		n;
	char	*ext;
	int		index;
	char	*clean;
	char	*t;


	// printf("in env_vr_check\n");

	tmp = mini->tokens;
	while (tmp)
	{
		i = 0;
		q_dom = 0;
		// if (tmp->cmd_args && tmp->cmd_args[0])
		if (tmp->cmd_args)
		// if (tmp->cmd_args && tmp->cmd_args[0] || tmp->type != 'd')

		{
			while(tmp->cmd_args[i])
			{
				j = 0;
				while(tmp->cmd_args[i][j])
				{
					n = 0;
					if((tmp->cmd_args[i][j] == '\"' || tmp->cmd_args[i][j] == '\'') && !q_dom)
					{
						// if (!q_dom)
						q_dom = tmp->cmd_args[i][j];
						j++;
						// printf("here %c\n", q_dom);
					}
					if((q_dom) && (tmp->cmd_args[i][j] == q_dom))
						q_dom = 0;
					if ((tmp->cmd_args[i][j] == '$') && (q_dom == '\"' || !q_dom))
					{
						j++;
					
						if (tmp->cmd_args[i][j] == '?')
						{
							s = tmp->cmd_args[i] + j;

							index = ft_strchr_nb(tmp->cmd_args[i], '$');
							// n = 1;
							ext = ft_itoa(g_exit);
							// printf("itoa %s\n", ext);
							if(!ext)
							{
								// printf("err\n");
								return (1);
							}							
							// n = ft_strlen(ext);
							s += 1;							
							// n = 1;

							clean = ft_insert(tmp->cmd_args[i], ext, -1, index);
							// printf("insert %s\n", clean);

							if(s)
							{
								t = tmp->cmd_args[i];
								tmp->cmd_args[i] = ft_strjoin(clean, s);
								// printf("after alteration %s\n", tmp->cmd_args[i]);	


								free(t);
								free(clean);
								// free(s);
							}
							else
							{
								t = tmp->cmd_args[i];
								tmp->cmd_args[i] = clean;
								free(t);
								// printf("after alteration %s\n", tmp->cmd_args[i]);	

							}
							// printf("after alteration %s\n", tmp->cmd_args[i]);	
							j = -1;
							q_dom = 0;

						}
						else
						{

					
							s = tmp->cmd_args[i] + j;
							// printf("ssss %s\n", s);

							index = ft_strchr_nb(tmp->cmd_args[i], '$');
							while((s[n] >= 'A' && s[n] <= 'Z') || (s[n] >= 'a' && s[n] <= 'z'))
							// while (s[n] && s[n] != ' ')
								n++;
							if (!n)
							{
								// printf("err\n");
								n++;
								if (!s[n])
									return (0);
								else
								j++;
								break ;
								
							}
							clean = strndup(s, n); //!!!
							// printf("clean is %s\n", clean);
							ext = get_env_str(mini->env, clean);
							// printf("ext is %s\n", ext);

							if (clean)
								free(clean);
							if(!ext)
							{
								// printf("err\n");
								// tmp->cmd_args[i] = extract(tmp->cmd_args[i], )
								// return (1);

								clean = tmp->cmd_args[i];
								j--;
								n++;
								tmp->cmd_args[i] = extract(tmp->cmd_args[i], j, n);
								if (clean)
									free(clean);
								j = -1;
								q_dom = 0;

								// return (0);
							}
							else
							{

								s += n;
							

								clean = ft_insert(tmp->cmd_args[i], ext, n, index);
							

								// free(clean);
								if(s)
								{
									t = tmp->cmd_args[i];
									tmp->cmd_args[i] = ft_strjoin(clean, s);
									// printf("after alteration %s\n", tmp->cmd_args[i]);	


									free(t);
									free(clean);
									// free(s);
								}
								else
								{
									t = tmp->cmd_args[i];
									tmp->cmd_args[i] = clean;
									free(t);
									// printf("after alteration %s\n", tmp->cmd_args[i]);	

								}
								// printf("after alteration %s\n", tmp->cmd_args[i]);	
								j = -1;
								q_dom = 0;
							}
						}
					}
					j++;
				}
				i++;
			}
		}
		
		tmp = tmp->next;
	}
	return (0);

}
