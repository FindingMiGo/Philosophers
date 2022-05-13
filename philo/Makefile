

SRCS =	main.c utils.c init.c debug.c

NAME = philo

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
DEBUG =

ifdef NO_FLAGS
CFLAGS =
endif

ifdef WITH_VALG
CFLAGS += -D DELAY=600
endif

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -pthread -o $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

nf :
	$(MAKE) fclean
	make NO_FLAGS=1

ht : fclean
	$(MAKE) WITH_VALG=1
	valgrind --tool=helgrind ./$(NAME) 10 200 100 100

hm : fclean
	$(MAKE) WITH_VALG=1
	valgrind ./$(NAME) 10 200 100 100

.PHONY:		all clean fclean re h
