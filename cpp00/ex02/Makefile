NAME		= banksters
SRC			= Account.cpp tests.cpp
OBJ			= $(SRC:.cpp=.o)
CC			= c++
CFLAGS		= -Wall -Wextra -Werror -std=c++98
LOG_FILE	= 19920104_091532.log


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f user.log user.cut ref.cut

fclean: clean
	rm -f $(NAME)

re: fclean all


test: $(NAME)
	./$(NAME) > user.log
	cut -c 18- user.log > user.cut
	cut -c 18- $(LOG_FILE) > ref.cut
	diff user.cut ref.cut
	@echo "✅ SUCCÈS ! Output is the same !!"
	@rm -f user.log user.cut ref.cut

.PHONY: all clean fclean re test
