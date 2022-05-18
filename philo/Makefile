CC =		clang #-fsanitize=address
NAME =		philo
SRCS_NAME =	actions.c \
			check_args.c \
			ft_error.c \
			ft_isdigit.c \
			ft_thread.c \
			init.c \
			philo.c \
			print.c \
			time.c

SRCS =		$(addprefix $(SRCS_PATH)/, $(SRCS_NAME))
SRCS_PATH =	srcs
INC_NAME =	philo.h
INC =		$(addprefix $(INC_PATH)/, $(INC_NAME))
INC_PATH =	includes
RM =		rm -rf
OBJ =		$(SRCS:.c=.o)
CFLAG =		-Wall -Wextra -Werror
INCFLAGS =	-I$(INC_PATH)

all :		 $(NAME)

%.o : %.c
			$(CC) $(CFLAG) $(INCFLAGS) -c $< -o $@

$(NAME) : 	$(OBJ) $(INC)
			$(CC) -o $@ $(OBJ) -lpthread

clean :
			$(RM) $(OBJ)

fclean :	clean
			$(RM) $(NAME) $(BONUSNAME) 

re : 		fclean all

.PHONY : 	all clean fclean re
