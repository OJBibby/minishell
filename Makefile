
NAME	= minishell

OBJ_DIR = obj/
SRC		= main.c get_args.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strchr.c libft/ft_strncmp.c \
			extension.c libft/ft_strlen.c libft/ft_isalpha.c quotes.c spaces.c libft/ft_split_or.c \
			libft/ft_strdup.c fin_token.c libft/ft_calloc.c libft/ft_strjoin_slash.c libft/ft_bzero.c \
			echo/echo.c cd/cd.c env/env.c env/utils.c exit/exit.c pwd/pwd.c \
			execute/execute.c execute/init.c execute/io.c execute/output.c \
			export/export.c signals/signals.c
OBJ		= $(SRC:%.c=$(OBJ_DIR)%.o)
CC		= gcc
#-g -fsanitize=address
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address
LIBS	= -lreadline
GREY	=	\33[1;30m
BLUE	=	\33[0;34m
GREEN	=	\33[0;32m

all : $(NAME)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(@D)
	@printf "\r                                         "
	@printf "\r$(GREY)Compiling $(BLUE)$<"
	@$(CC) -c -g $< -o $@

$(NAME) : $(OBJ) minishell.h Makefile
	@printf "\r$(GREY)Compiling $(BLUE)$(NAME)        \n"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

clean :
	@printf "$(GREY)Removing $(BLUE)$(OBJ)\n"
	@rm -fr $(OBJ_DIR)

fclean : clean
	@printf "$(GREY)Removing $(BLUE)$(NAME)\n"
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re