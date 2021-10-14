# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ade-la-c <ade-la-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 19:35:02 by ade-la-c          #+#    #+#              #
#    Updated: 2021/10/14 17:28:31 by ade-la-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= philo

SRCS				= srcs/main.c \
					srcs/utils/utils.c \
					srcs/utils/lib_utils.c \
					srcs/actions.c \
					srcs/threading.c \

OBJS				= $(SRCS:.c=.o)

CC					= gcc #-g3

RM					= rm -f

CFLAGS				= -Wall -Werror -Wextra -pthread -I. #-g -fsanitize=address

CL_GREY				= \033[38;2;128;128;128m

CL_GREEN			= \033[38;2;0;153;0m

CL_RESET			= \033[0m

.c.o:
					@${CC} ${CFLAGS} -c $^ -o $@

all:			$(NAME)

$(NAME):		$(OBJS)
					@echo "$(CL_GREEN)-> COMPILING PHILOSOPHERS <-$(CL_RESET)"
					@echo "$(CL_GREY)"
					$(CC) ${CFLAGS} -o$(NAME) $(OBJS)
					@echo "$(CL_RESET)"

clean:
					@echo "$(CL_GREEN)-> CLEAN$(CL_RESET)"
					$(RM) $(OBJS)
					@echo "$(CL_RESET)"

fclean:			clean
					@echo "$(CL_GREEN)-> FCLEAN$(CL_RESET)"
					$(RM) $(NAME)
					@echo "$(CL_RESET)"

re:				fclean all

mclean:			all clean

.PHONY:			all clean fclean mclean re
