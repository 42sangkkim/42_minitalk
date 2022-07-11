# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/11 10:12:59 by sangkkim          #+#    #+#              #
#    Updated: 2022/07/11 11:07:06 by sangkkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mknitalk

SERVER = server
CLIENT = client

SERVER_SRCS = server.c ../utils1.c ../utils2.c
CLIENT_SRCS = client.c ../utils1.c ../utils2.c

CC = cc
CFLAGS = -Wall -Wextra -Werror

$(NAME) : $(SERVER) $(CLIENT)
	cp $(SERVER) ../
	cp $(CLIENT) ../

$(SERVER) : $(SERVER_SRCS) $(INCS)
	$(CC) $(CFLAGS) $(SERVER_SRCS) -o $@

$(CLIENT) : $(CLIENT_SRCS) $(INCS)
	$(CC) $(CFLAGS) $(CLIENT_SRCS) -o $@

.PHONY : all clean fclean re

all : $(NAME)

clean :
	rm -f $(SERVER) $(CLIENT)

fclean : clean
	rm -f ../$(SERVER) ../$(CLIENT)

re : fclean all