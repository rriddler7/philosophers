NAME =	philo_bonus

SRC = ./utils.c ./init_philo.c ./simulate.c ./philo.c

OBJ = $(SRC:.c=.o)

HEADER = philo_bonus.h

CC = gcc

FLAGS = -Wall -Wextra -Werror

all : $(NAME)

%.o: $(SRC)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@ -I $(HEADER)

$(NAME): $(OBJ) $(HEADER) Makefile
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
