# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adriouic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/13 19:11:24 by adriouic          #+#    #+#              #
#    Updated: 2022/02/13 19:15:05 by adriouic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = src/drowonwindow.c src/get_color.c src/interaction.c src/key_handler.c src/parser.c

GNL_FILES = get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

FLAGS = -Wall -Werror -Wextra

OPEN_GL = -lmlx -framework OpenGL -framework AppKit

#D = -I /usr/X11/include -g -L /usr/X11/lib -l mlx -framework OpenGL -framework AppKit

NAME = fdf

all: $(NAME)

$(NAME):  LIB
	cc $(FLAGS)  -L./libft -lft $(FILES) $(GNL_FILES) $(OPEN_GL) -o $@

LIB:
	make -C ./libft
	make bonus -C ./libft

clean:
	make clean -C ./libft
	
fclean: clean
	rm -rf $(NAME)
	make fclean -C ./libft

re: fclean all

