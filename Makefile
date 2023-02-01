
NAME	= minishell

OBJ_DIR = obj/
SRC_DIR	= src/
SRC		= main.c parsing/get_args.c parsing/clean_args.c parsing/path.c parsing/ext_if_var.c parsing/free.c parsing/parsing.c \
			parsing/redir_in.c parsing/redir_out.c parsing/utils_ext.c parsing/utils_fin_token.c parsing/utils_get_args.c parsing/utils_one.c \
			parsing/utils_redir.c parsing/extension.c parsing/quotes.c parsing/spaces.c libft/ft_atoi.c libft/ft_strjoin.c libft/ft_strchr.c \
			libft/ft_strlen.c libft/ft_isalpha.c libft/ft_strdup.c libft/ft_strndup.c parsing/fin_token.c libft/ft_calloc.c libft/ft_strjoin_slash.c \
			libft/ft_bzero.c libft/ft_itoa.c libft/ft_putstr_fd.c libft/ft_strncmp.c libft/ft_split_or.c echo/echo.c echo/utils.c \
			cd/cd.c env/env.c env/utils.c env/path.c env/node.c exit/exit.c pwd/pwd.c execute/execute.c execute/init.c execute/io.c \
			execute/output.c execute/utils.c export/export.c export/utils.c signals/signals.c
SRCS	=	$(addprefix $(SRC_DIR), $(SRC))
OBJ		= $(SRCS:%.c=$(OBJ_DIR)%.o)
INC		= inc/execute.h inc/minishell.h
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
LIBS	= -L/usr/local/opt/readline/lib -lreadline
#INCLUDE = -I/usr/local/opt/readline/include
GREY	=	\33[1;30m
BLUE	=	\33[0;34m
GREEN	=	\33[0;32m
RESET	=	\33[0m

all : $(NAME)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(@D)
	@printf "\33[2K\r$(GREY)Compiling $(BLUE)$<"
	@$(CC) -c -g $< -o $@ $(INCLUDE)

$(NAME) : $(OBJ) $(INC)
	@printf "\33[2K\r$(GREY)Compiling $(BLUE)$(NAME)$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

clean :
	@printf "$(GREY)Removing $(BLUE)$(OBJ)$(RESET)\n"
	@rm -fr $(OBJ_DIR)

fclean : clean
	@printf "$(GREY)Removing $(BLUE)$(NAME)$(RESET)\n"
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re