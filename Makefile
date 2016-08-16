NAME = fdf

FLAG = -Wall -Werror -Wextra

SRC = fdf.c\
	tool.c\
	ft_parse_map.c\
	get_next_line/get_next_line.c

OBJ= fdf.o\
	 tool.o\
	ft_parse_map.o\
	get_next_line.o

all: $(NAME)

$(NAME): $(SRC)
	make -C ./libft
	gcc $(FLAG) -c $(SRC)
	gcc -L./libft -lft -L/usr/local/lib/ -I/usr/local/include -lmlx -framework OpenGL -framework AppKit $(OBJ) -o $(NAME)

clean:
	make -C ./libft clean
	rm -f $(OBJ)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all
