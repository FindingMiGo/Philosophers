

SRC =	main.c utils.c init.c locked_val.c act.c routine.c thread.c termination.c mutex.c time.c debug.c

SRCDIR = srcs

SRCS = $(addprefix $(SRCDIR)/, $(SRC))

INCLUDE =	-I./includes/

NAME = philo

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEBUG =

ifdef WITH_SANITIZE
DEBUG = -fsanitize=thread
endif

.c.o :
	$(CC) $(CFLAGS) $(DEBUG) $(INCLUDE) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(DEBUG) -pthread $(INCLUDE) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

hel : re
	valgrind --tool=helgrind ./$(NAME) 200 420 100 100

val : re
	valgrind ./$(NAME) 200 410 200 200

san : fclean
	make WITH_SANITIZE=1
	./$(NAME) 200 410 200 200

.PHONY:		all clean fclean re hel val san
