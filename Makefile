NAME = Pokemon

CC = cc
CFLAGS = -g -Wall -Wextra -Werror

RM = rm -f

SRC_FILES = ./Source/execution.c \
			./Source/linked_list.c \
			./Source/market.c \
			./Source/pokemon.c \
			./Source/parse.c \
			./Source/travel.c \
			./Source/save.c \
			./Source/utils.c
SRC_OBJ = $(SRC_FILES:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(SRC_OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC_OBJ)
	@echo "\033[47;30m* $(NAME) was created *\033[0m"

clean:
	$(RM) $(SRC_OBJ)

fclean:
	make clean
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re