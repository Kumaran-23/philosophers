NAME = philo
SRC = philo.c init.c \
utils.c get_time.c \
death_eat_check.c free_destroy.c \
routine.c error_check.c 
HEADER = philo.h
OBJ = $(SRC:.c=.o)
CC = gcc
FLAGS = -g -Wall -Werror -Wextra -pthread

GREEN		=	\033[1;92m
YELLOW		=	\033[1;93m
BLUE		=	\033[0;94m
WHITE		=	\033[0;97m

start:
			@echo "$(YELLOW)Start Make:$(WHITE)"
			@make all
			
all: $(NAME)

$(NAME): $(HEADER) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)philo Done!$(WHITE)"

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "$(BLUE)philo: object files have been cleaned!$(WHITE)"


fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)philo: files have been cleaned!$(WHITE)"

re: fclean all
	@echo "$(GREEN)Cleaned and rebuilt everything for philo\n$(WHITE)"


.PHONY: all clean fclean re