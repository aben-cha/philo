NAME	= philo_bonus
CC 		= cc
CFLAGS	= -Wall -Wextra -Werror
SRC		= philo_bonus.c parsing_bonus.c init_bonus.c simulation_bonus.c \
	utils_bonus.c routine_bonus.c getters_setters_bonus.c
OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -pthread -o $(NAME)

%.o: %.c philo_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean