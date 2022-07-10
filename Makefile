# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sangkkim <sangkkim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/07 12:46:42 by sangkkim          #+#    #+#              #
#    Updated: 2022/07/07 22:37:18 by sangkkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:=minitalk

SERVER_DIR:=server
SERVER:=server

CLIENT_DIR:=client
CLIENT:=client

$(NAME) : $(SERVER) $(CLIENT)


.PHONY : all clean fclean re bonus

all : $(NAME)

clean :
	make -C $(SERVER_DIR) clean
	make -C $(CLIENT_DIR) clean

fclean :
	$(RM) $(RMFLAGS) $(SERVER) $(CLIENT)



