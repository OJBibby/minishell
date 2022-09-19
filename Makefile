
NAME	= minishell

OBJ_DIR = obj/
SRC		= main.c get_args.c ft_split.c ft_strjoin.c ft_strchr.c ft_strncmp.c \
			extension.c ft_strlen.c ft_isalpha.c quotes.c spaces.c ft_split_or.c \
			ft_strdup.c fin_token.c ft_calloc.c ft_strjoin_slash.c ft_bzero.c \
			echo/echo.c cd/cd.c env/env.c exit/exit.c pwd/pwd.c pipex/pipex.c
OBJ		= $(SRC:%.c=$(OBJ_DIR)%.o)

CC		= clang
# CFLAGS	= -Wall -Wextra -Werror -lreadline -fsanitize=address -g
CFLAGS	= -Wall -Wextra -Werror -lreadline -g -fsanitize=address
GREY	=	\33[1;30m
BLUE	=	\33[0;34m


all : $(NAME)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(@D)
	@printf "\r                               "
	@printf "\r$(GREY)Compiling $(BLUE)$<"
	@$(CC) -c -g $< -o $@

$(NAME) : $(OBJ) minishell.h Makefile
	@printf "\r$(GREY)Compiling $(BLUE)$(NAME)     	\n"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean :
	@printf "$(GREY)Removing $(BLUE)$(OBJ)\n"
	@rm -fr $(OBJ_DIR)

fclean : clean
	@printf "$(GREY)Removing $(BLUE)$(NAME)\n"
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re