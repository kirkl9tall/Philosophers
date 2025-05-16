NAME = philo
SRC = routine.c parcing.c init_monit.c extra_routine.c main.c
CC = cc -g
CFLAGS = -Werror -Wextra -Wall
RM = rm -rf
OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME):$(OBJ) 
	$(CC) $(CFLAGS) $(OBJ)  -o $(NAME)

re:fclean all

clean:
	$(RM) $(OBJ)

fclean:clean
	$(RM) $(NAME)

.PHONY: fclean clean re all 