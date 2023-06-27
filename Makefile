# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lholdo <lholdo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 16:11:05 by lholdo            #+#    #+#              #
#    Updated: 2021/10/25 16:31:22 by lholdo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	  = ./src/color.c ./src/controls.c ./src/copy.c ./src/fdf_utils.c ./src/projection.c \
	./src/read_map.c ./src/utils.c ./src/mouse.c ./src/draw.c ./src/draw_utils.c ./src/iso_and_rotate.c \
	./src/reallocation.c ./src/read_map_utils.c ./src/free.c
NAME	  = fdf.a
OBJS	  =  ${SRCS:.c=.o}
LIBFT     = ./libft/
GNL       = ./get_next_line/
LIBNAME   = libft.a
GNLNAME = get_next_line.a
EXE       = push_swap
MINILIBX = ./minilibx_macos/
UTILS = -framework OpenGL -framework AppKit -g
FLAGS = -MMD -Wall -Werror -Wextra -g3
LIB = ${LIBFT}/${LIBNAME} ${GNL}/${GNLNAME} -L ${MINILIBX}/minilibx.a

all : ${NAME}
		make -C ${MINILIBX}
		make -C ${LIBFT}
		make -C ${GNL}
		make exec

exec: ${NAME}
	gcc {FLAGS} ./src/fdf.c ${NAME} ${LIB} ${UTILS} -o ${EXE}


.c.o	:
		gcc ${FLAGS} -c $< -o ${<:.c=.o}


${NAME} : ${OBJS}
		ar rc ${NAME} ${OBJS}

clean :
		rm -f ${OBJS} exec
		rm -f ${EXE}
		make clean -C ${LIBFT}
		make clean -C ${GNL}

fclean : clean
		rm -f ${NAME}
		make fclean -C ${LIBFT}
		make fclean -C ${GNL}

re : fclean all
