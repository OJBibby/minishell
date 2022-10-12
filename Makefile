
NAME	= minishell

OBJ_DIR = obj/
SRC		= main.c get_args.c clean_args.c path.c ext_if_var.c free.c parsing.c redir_in.c redir_out.c \
			utils_ext.c utils_fin_token.c utils_get_args.c utils_one.c utils_redir.c extension.c quotes.c \
			spaces.c libft/ft_atoi.c libft/ft_strjoin.c libft/ft_strchr.c libft/ft_strlen.c libft/ft_isalpha.c \
			libft/ft_strdup.c libft/ft_strndup.c fin_token.c libft/ft_calloc.c libft/ft_strjoin_slash.c libft/ft_bzero.c \
			libft/ft_itoa.c libft/ft_putstr_fd.c libft/ft_strncmp.c libft/ft_split_or.c echo/echo.c cd/cd.c env/env.c \
			env/utils.c exit/exit.c pwd/pwd.c execute/execute.c execute/init.c execute/io.c execute/output.c \
			export/export.c signals/signals.c
OBJ		= $(SRC:%.c=$(OBJ_DIR)%.o)
CC		= gcc
#-g -fsanitize=address
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address
LIBS	= -L/usr/local/opt/readline/lib -lreadline
INCLUDE = -I/usr/local/opt/readline/include
GREY	=	\33[1;30m
BLUE	=	\33[0;34m
GREEN	=	\33[0;32m
RESET	=	\33[0m

all : $(NAME)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(@D)
	@printf "\r                                         "
	@printf "\r$(GREY)Compiling $(BLUE)$<"
	@$(CC) -c -g $< -o $@ $(INCLUDE)

$(NAME) : $(OBJ) minishell.h Makefile
	@printf "\r$(GREY)Compiling $(BLUE)$(NAME)$(RESET)        \n"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

clean :
	@printf "$(GREY)Removing $(BLUE)$(OBJ)$(RESET)\n"
	@rm -fr $(OBJ_DIR)

fclean : clean
	@printf "$(GREY)Removing $(BLUE)$(NAME)$(RESET)\n"
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re