

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

nf :
	$(MAKE) fclean
	make NO_FLAGS=1

ht : re
	valgrind --tool=helgrind ./$(NAME) 200 420 100 100 1

hm : re
	valgrind ./$(NAME) 10 200 100 100

san : fclean
	make WITH_SANITIZE=1

.PHONY:		all clean fclean re san
