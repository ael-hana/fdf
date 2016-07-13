NAME=fdf
FLAG= -Wall -Werror -Wextra
SRC= ./src/fdf.c\
     ./src/fdf_draw.c\
     ./src/fdf_parse.c\
     ./src/fdf_misc.c\
     ./src/fdf_color.c\
     ./src/fdf_split.c
OBJ= ./fdf.o\
     ./fdf_draw.o\
     ./fdf_parse.o\
     ./fdf_misc.o\
     ./fdf_color.o\
     ./fdf_split.o
all : $(NAME)

$(NAME) : $(SRC)
     make -C libft/
     make -C minilibx/
     gcc $(FLAG) -I./ -c $(SRC)
     gcc -L./libft -L./minilibx -lft -lmlx -framework OpenGL -framework Appkit $(OBJ) -o $(NAME)

clean :
    make -C ./libft clean
    make -C ./minilibx clean
    rm -f $(OBJ)

fclean : clean
    make -C ./libft fclean
    rm -f $(NAME)

re : fclean all
