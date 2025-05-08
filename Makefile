CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

TARGET = philo

SRCS = philo.c init.c parsing.c utils.c errors.c actions.c checks.c cleanup.c routine.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS) philo.h
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
