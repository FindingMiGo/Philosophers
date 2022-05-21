

SRC =	main.c utils.c init.c locked_val.c act.c\
		routine.c thread.c termination.c mutex.c time.c

SRCDIR =	srcs

SRCS =	$(addprefix $(SRCDIR)/, $(SRC))

INCLUDE =	-I./includes/

NAME =	philo

OBJS =	$(SRCS:.c=.o)

CC =	gcc
CFLAGS = -Wall -Wextra -Werror

ifdef WITH_SANITIZE
CFLAGS += -g -fsanitize=thread
endif

.c.o :
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -pthread $(INCLUDE) -o $(NAME) $(OBJS)

all:	$(NAME)

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:		fclean all

san :	fclean
		make WITH_SANITIZE=1

.PHONY:		all clean fclean re hel val san
