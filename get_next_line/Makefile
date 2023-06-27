# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ale-roux <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/06 21:21:04 by ale-roux          #+#    #+#              #
#    Updated: 2022/11/14 15:20:30 by ale-roux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= get_next_line.c get_next_line_utils.c
SRCS_BON 	= get_next_line_bonus.c get_next_line_utils_bonus.c
NAME		= get_next_line.a
NAME_BON	= get_next_line_bonus.a
OBJS		=  ${SRCS:.c=.o}
OBJS_BON 	= ${SRCS_BON:.c=.o}

.c.o	:
		gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

${NAME} : ${OBJS}
		ar rc ${NAME} ${OBJS}

${NAME_BON} : ${OBJS_BON}
		ar rc ${NAME} ${OBJS_BON}


all : ${NAME}

bonus : ${NAME_BON}

clean :
		rm -f ${OBJS}
		rm -f ${OBJS_BON}

fclean : clean
		rm -f ${NAME}
		rm -f ${NAME_BON}

re : fclean all
