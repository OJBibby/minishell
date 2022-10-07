#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <signal.h>

// token is what keeps info about each command,
// one token equals to one command.
// **cmd_args – array of arguments where cmd_args[0] is the name of the command
// path – path to the executable

extern int	g_exit;

typedef struct s_glue
{
	int		bg_arg;
	int		bg_chr;
	int		end_arg;
	int		end_chr;
}	t_glue;

typedef struct s_token
{
	char *cmd_name; // !do not use! (will be removed later)
	char **cmd_args;
	char *path;
	char **input;
	char **output;
	int *heredoc;
	int *append;
	char type;
	bool d_quotes;
	struct s_token *next;
	struct s_token *prev;
} t_token;

typedef struct s_env
{
	char *str;
	struct s_env *next;
	struct s_env *prev;
} t_env;

// tokens – pointer to the list of command tokens
// env – pointer to the environment in a for of a list
typedef struct s_mini
{

	// int		prompt;
	t_env *env;
	t_token *tokens;
	int	pid;
} t_mini;

int parsing(t_mini *mini);
char **ft_split(char *s, char c, t_mini *mini, t_token *token);
char *get_cmd_name(t_mini *mini, char *str, t_token *token);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strchr(const char *s, int c);
int ft_strchr_nb(const char *s, int c);
int ft_strncmp(const char *s1, const char *s2, size_t n);
t_env *get_env_node(t_env *env, char *var);
char *get_env_str(t_env *env, char *var);
size_t ft_strlen(const char *s);
int ft_isupper(int c);
int check_env_vr(t_mini *mini);
int quotes(t_mini *mini, t_token *tmp);
int mng_spaces(t_mini *mini);
int mng_quotes(t_mini *mini);
char *ft_remove(char *str, int *j, char c);
char *ft_remove_q(char *str, int *j, char c);
char **ft_split_or(char const *s, char c);
char *ft_strdup(const char *s1);
int execution(t_mini *mini);
int ft_islower(int c);
int ft_isdigit(int c);
int check_path(t_mini *mini, t_token *token);
int fin_token(t_mini *mini);
int ft_isalpha(int c);
int free_token(t_mini *mini);
void free_d_arr(char **arr);
int free_token_light(t_token *tokens);
void	glue(t_token *token);
int		mng_quotes_light(char **arr);
int	execute(t_mini *mini);
void	ft_bzero(void *str, size_t n);
int	free_env(t_mini *mini);
void	*ft_calloc(size_t elenum, size_t size);
void	sig_quit(int i);
void	sig_int(int	sig);
int		ft_strncmp_env(const char *s1, const char *s2, size_t n);
char	**list_to_arr(t_env *env);
char	*ft_itoa(int n);
void	clean_args(t_token *token);
int		ft_strncmp_mod(const char *s1, const char *s2, size_t n);
int		check_builtin(char **args);
int		ft_strncmp_p(const char *s1, const char *s2, size_t n);
int		free_env(t_mini *mini);
void	my_print(t_token *token);
int		get_args(t_mini *mini, char *str, t_token *token);
char	**add_string(char **arr, char *str);

#endif