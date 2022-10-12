#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>

# define B_ERR "\n⚜️ 𝔗𝔥𝔢 𝔰𝔱𝔯𝔦𝔫𝔤 𝔡𝔬𝔢𝔰𝔫'𝔱 𝔞𝔭𝔭𝔢𝔞𝔯 𝔱𝔬 𝔟𝔢 𝔳𝔞𝔩𝔦𝔡, 𝔜𝔬𝔲𝔯 𝔐 𝔞𝔧𝔢𝔰𝔱𝔶 ⚜️\n\n"
# define GRT "\n⚜️ 𝔊 𝔯𝔢𝔢𝔱𝔦𝔫𝔤𝔰, 𝔜𝔬𝔲𝔯 𝔐 𝔞𝔧𝔢𝔰𝔱𝔶. 𝔚 𝔥𝔞𝔱 𝔴𝔦𝔩𝔩 𝔟𝔢 𝔜𝔬𝔲𝔯 𝔠𝔬𝔪𝔪𝔞𝔫𝔡𝔰? ⚜️\n\n"
# define BYE "\n\n⚜️ 𝔥𝔞𝔳𝔢 𝔞 𝔟𝔩𝔢𝔰𝔰𝔢𝔡 𝔡𝔞𝔶, 𝔜𝔬𝔲𝔯 𝔐 𝔞𝔧𝔢𝔰𝔱𝔶 ⚜️\n\n"
# define CMD "\n🗡️ ℑ 𝔡𝔢𝔠𝔩𝔞𝔯𝔢 𝔴 𝔦𝔱𝔥 𝔰𝔬𝔯𝔯𝔬𝔴 𝔱𝔥𝔞𝔱 𝔫𝔬 𝔰𝔲𝔠𝔥 𝔠𝔬𝔪𝔪𝔞𝔫𝔡 𝔴𝔞𝔰 𝔣𝔬𝔲𝔫𝔡\n"
# define QUO "\n🗡️ 𝔖 𝔦𝔩𝔩𝔶 𝔪𝔢 𝔠𝔞𝔫'𝔱 𝔪𝔞𝔨𝔢 𝔰𝔢𝔫𝔰𝔢 𝔬𝔣 𝔱𝔥𝔢 𝔮𝔲𝔬𝔱𝔢 𝔪𝔞𝔯𝔨𝔰\n"
# define SPC "\n🗡️ 𝔒𝔥 𝔫𝔬! 𝔗𝔥𝔢 𝔱𝔥𝔢 𝔭𝔦𝔭𝔢𝔰 𝔥𝔞𝔳𝔢 𝔡𝔢𝔪𝔬𝔫𝔰 𝔦𝔫𝔰𝔦𝔡𝔢 𝔱𝔥𝔢𝔪!\n"
# define SYN "\n🗡️ 𝔗𝔥𝔢 𝔰𝔶𝔫𝔱𝔞𝔵 𝔡𝔬𝔢𝔰 𝔫𝔬𝔱 𝔞𝔩𝔦𝔤𝔫 𝔴𝔦𝔱𝔥 𝔱𝔥𝔢 𝔟𝔞𝔰𝔥 𝔰𝔠𝔯𝔦𝔭𝔱𝔲𝔯𝔢𝔰\n"

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
	char			*cmd_name;
	char			**cmd_args;
	char			*path;
	char			**input;
	char			**output;
	int				*heredoc;
	int				*append;
	char			type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_mini
{
	t_env	*env;
	t_token	*tokens;
	t_token	*tm;
	int		pid;
}	t_mini;

typedef struct s_util
{
	int		olen;
	int		ilen;
	t_token	*old;
	t_token	*ret;
	t_token	*head;
	int		exit;
}	t_util;

typedef struct s_ext
{
	char	q_dom;
	char	*s;
	int		n;
	char	*ext;
	int		index;
	char	*clean;
	char	*t;
	t_mini	*mini;
	int		exit;
}	t_ext;

typedef struct s_arg
{
	int		tk_counter;
	int		exit;
	t_token	*new;
	t_token	*head;
	char	*tmp;
	char	q_char;
	char	**tmp_arr;
}	t_arg;

typedef struct s_quo
{
	bool	dom_cl;
	bool	dom_op;
	char	dom;
}	t_quo;

int			parsing(t_mini *mini);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strchr(const char *s, int c);
int			ft_strchr_nb(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
t_env		*get_env_node(t_env *env, char *var);
char		*get_env_str(t_env *env, char *var);
size_t		ft_strlen(const char *s);
int			ft_isupper(int c);
int			check_env_vr(t_mini *mini);
int			quotes(t_token *tmp);
int			mng_spaces(t_mini *mini);
char		*ft_remove(char **str, int *j, char c);
char		*ft_remove_q(char *str, int *j, char c);
char		**ft_split_or(char const *s, char c);
char		*ft_strdup(const char *s1);
int			ft_islower(int c);
int			ft_isdigit(int c);
int			check_path(t_mini *mini, t_token *token);
int			fin_token(t_mini *mini);
int			ft_isalpha(int c);
int			free_token(t_mini *mini);
void		free_d_arr(char **arr);
int			free_token_light(t_token *tokens);
int			mng_quotes_light(char **arr);
char		*ft_itoa(int n);
void		clean_args(t_token *token);
int			ft_strncmp_mod(const char *s1, const char *s2, size_t n);
int			check_builtin(char **args);
int			ft_strncmp_p(const char *s1, const char *s2, size_t n);
int			free_env(t_mini *mini);
void		my_print(t_token *token);
int			get_args(t_mini *mini, char *str, t_token *token);
char		**add_string(char **arr, char *str);
t_token		*init_token(void);
void		init_in_out(t_token *token);
int			ft_putstr_fd(char *s, int fd);
int			redir_in(t_util *ut, int *i, int *j);
int			redir_out(t_util *ut, int *i, int *j);
char		**copy_args(char **from, int n);
int			*add_int(int *arr, int nb, int q, int len);
int			if_var(t_ext *ex, int *i, int *j, t_mini *mini);
char		*ft_insert(char *s1, char *point_of_in, int remove, int index);
char		*extract(char *str, int start, int n);
void		init_var(t_util *ut, int *i, int *j, t_mini *mini);
char		**put_pipe(void);
int			mng_token_list(t_util *ut);
int			tokenize(t_arg *ar, t_token *token, int *i, char **str);
int			separate(char *str, t_token *token);
int			check_valid_args(t_util *ut);
void		mod_append(t_util *ut, int i);
void		mod_heredoc(t_util *ut, int i);
char		*ft_strndup(const char *s1, int n);
int			execute(t_mini *mini);
void		sig_quit(int sig);
void		sig_int(int sig);
void		*ft_calloc(size_t elenum, size_t size);
void		ft_bzero(void *str, size_t n);


#endif