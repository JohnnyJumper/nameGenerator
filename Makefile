NAME= genName
CC = gcc
Flags = -Wall -Wextra -Werror -g

DEPS = genName.h
SRC = main.c parser.c generator.c alphabet.c 
OBJ = $(SRC:.c=.o);


all: $(NAME)
	@echo "Compiled"

$(NAME): $(OBJ)
	${CC} ${Flags} $^ -o $@


%.o : %.c
	$(CC) $(Flags) -c $< -o $@

clean: 
	@rm $(OBJ)
	@rm $(NAME)
	@echo "cleaned"
	
re: clean all