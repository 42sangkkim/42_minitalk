# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sangkkim <sangkkim@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/08 16:09:33 by sangkkim          #+#    #+#              #
#    Updated: 2022/07/08 16:51:53 by sangkkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:=client

M_SRCS:=client.c utils.c
B_SRCS:=client_bonus.c utils.c

CC:=cc
CFLAGS:=-Wall -Wextra -Werror

RM:=rm
RMFLAGS:=-f

ifdef BONUS
SRCS=$(B_SRCS)
else
SRCS=$(M_SRCS)
endif

$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY : all clean fclean re bonus

all : $(NAME)

clean :
	$(RM) $(RMFLAGS) $(NAME)

fclean : clean

re : fclean all

bonus :
	make BONUS=1 all
