NAME = megaphone
SRC = megaphone.cpp

OBJ = $(SRC:.c=.o)
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

rebonus: fclean all

.PHONY: clean fclean re all
