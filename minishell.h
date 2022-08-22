#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>




// token is what keeps info about each command,
// one token equals to one command.
// **cmd_args – array of arguments where cmd_args[0] is the name of the command
// path – path to the executable


typedef struct s_token
{
	char	*cmd_name; // !do not use! (will be removed later) 
	char	**cmd_args;
	char	*path;
	char	*infile;
	char	*outfile;
	struct s_token	*next;
	bool	d_quotes;
}		t_token;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
	struct s_env	*prev;
}		t_env;

// tokens – pointer to the list of command tokens
// env – pointer to the environment in a for of a list
typedef struct s_mini
{

	// int		prompt;
	t_env	*env;
	t_token	*tokens;
}		t_mini;

int	parsing(t_mini *mini);
char	**ft_split(char *s, char c, t_mini *mini, t_token *token);
char	*get_cmd_name(t_mini *mini, char *str, t_token *token);
int		pipex(t_mini *mini, char **env);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_slash(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
int	ft_strchr_nb(const char *s, int c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_bzero(void *str, size_t n);
void	*ft_calloc(size_t elenum, size_t size);
t_env	*get_env_node(t_env *env, char *var);
char	*get_env_str(t_env *env, char *var);
size_t	ft_strlen(const char *s);
int	ft_isupper(int c);
int	check_env_vr(t_mini *mini);
int	quotes(t_mini *mini, t_token *tmp);
int	mng_spaces(t_mini *mini);
int	mng_quotes(t_mini *mini);
char	*ft_remove(char *str, int *j, char c);
char	*ft_remove_q(char *str, int *j, char c);
char	**ft_split_or(char const *s, char c);
char	*ft_strdup(const char *s1);
int		execution(t_mini *mini);



#endif