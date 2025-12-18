NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = \
	get_next_line_utils.c ; get_next_line.c 
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all
