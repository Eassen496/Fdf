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

SRCS			= ./src/fdf_utils1.c ./src/fdf_utils2.c ./src/fdf_utils3.c ./src/fdf_verif1.c ./src/fdf_verif2.c ./src/fdf_draw.c ./design.c
NAME	  		= fdf.a
OBJS	  		=  ${SRCS:.c=.o}
MINILIBX 		= ./minilibx
MINILIBX_NAME  	= minilibx.a
EXE       		= fdf
FLAGS			= -Wall -Werror -Wextra
LIB				= -lmlx -framework OpenGL -framework AppKit

all : ${NAME}
		make -C ${MINILIBX}
		make exec

exec: ${NAME}
	gcc ${FLAGS} ./srcs/main.c ${NAME} ${MINILIBX}/${MINILIBX_NAME} -o ${EXE}


.c.o	:
		gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o}


${NAME} : ${OBJS}
		ar rc ${NAME} ${OBJS}

clean :
		rm -f ${OBJS} exec
		rm -f ${MINILIBX_NAME}
		make clean -C ${MINILIBX}

fclean : clean
		rm -f ${NAME}
		rm -f ${EXE}
		make fclean -C ${MINILIBX}

re : fclean all
