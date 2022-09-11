
NAME	= minishell

SRC		= main.c get_args.c ft_split.c ft_strjoin.c ft_strchr.c ft_strncmp.c \
			extension.c ft_strlen.c ft_isalpha.c quotes.c spaces.c ft_split_or.c \
			ft_strdup.c ft_calloc.c ft_bzero.c ft_strjoin_slash.c pipex/pipex.c \
			echo/echo.c exit/exit.c
OBJ		= $(SRC:.c=.o)

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
LFLAGS	= -lreadline

all : $(NAME)

%.o : %.c
	$(CC) -c $< -o $@

$(NAME) : $(OBJ) minishell.h Makefile
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LFLAGS)

clean :
	rm -f $(OBJ)

fclean : clean
	rm $(NAME)

re : fclean all

.PHONY : all clean fclean re