NAME	= philo
CC 		= cc
CFLAGS	= -Wall -Wextra -Werror
SRC		= philo.c parsing.c init.c simulation.c utils.c \
	routine.c getters_setters.c
OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -pthread -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean