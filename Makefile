NAME= genName
CC = gcc
Flags = -Wall -Wextra -Werror

all: ${NAME}
	@echo "Compiled"

${NAME}:
	${CC} ${Flags} main.c -o ${NAME}

clean: 
	@rm ${NAME}
	@echo "cleaned"
	
re: clean all