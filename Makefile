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

SRCS	= 
NAME	= so_long.a
OBJS	=  ${SRCS:.c=.o}

all : ${NAME} so_long

.c.o	:
		gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

so_long: ${NAME}
	gcc -Wall -Werror -Wextra so_long.c ${NAME} ./MLX42/libmlx42.a -ldl -lglfw -pthread -lm -L "/Users/ale-roux/.brew/opt/glfw/lib/"

${NAME} : ${OBJS}
		ar rc ${NAME} ${OBJS}

test : clean
	gcc main.c design.c -Werror -Wextra -Wall ./MLX42/libmlx42.a -I include -lglfw -L "/Users/ale-roux/.brew/opt/glfw/lib/" -o test

rt : clean test

clean :
		rm -f ${OBJS} test

fclean : clean
		rm -f ${NAME}

re : fclean all
