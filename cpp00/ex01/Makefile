NAME = phonebook

# Attention à la majuscule de PhoneBook.cpp si ton fichier a un B majuscule !
SRC = PhoneBook.cpp Contact.cpp main.cpp

# 1. On remplace .cpp par .o (et pas .c !)
OBJ = $(SRC:.cpp=.o)

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

# Règle par défaut
all: $(NAME)

# 2. L'édition de liens (Linking)
# On crée l'exécutable à partir des .o
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# 3. La compilation (Compiling)
# Règle générique : Comment transformer un .cpp en .o
# $< = le fichier source (.cpp)
# $@ = le fichier cible (.o)
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
