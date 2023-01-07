# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ale-roux <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 22:20:43 by ale-roux          #+#    #+#              #
#    Updated: 2022/12/15 23:22:45 by ale-roux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ./src/fdf_utils1.c ./src/fdf_utils2.c ./src/fdf_utils3.c ./src/fdf_verif1.c ./src/fdf_verif2.c
NAME	= fdf.a
OBJS	=  ${SRCS:.c=.o}

all : ${NAME} fdf

.c.o	:
		gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

fdf: ${NAME}
	gcc -Wall -Werror -Wextra main.c ${NAME} ./MLX42/libmlx42.a -ldl -lglfw -pthread -lm -L "/Users/ale-roux/.brew/opt/glfw/lib/"

${NAME} : ${OBJS}
		ar rc ${NAME} ${OBJS}

test : clean ${NAME}
	gcc main.c design.c -Werror -Wextra -Wall  ${NAME} ./MLX42/libmlx42.a -I include -lglfw -L "/Users/ale-roux/.brew/opt/glfw/lib/" -o test

clean :
		rm -f ${OBJS} test

fclean : clean
		rm -f ${NAME}

re : fclean all
