NAME := server

CC := cc
CFLAGS := -Wall -Wextra -Werror

RM := rm
RMFLAGS := -f

SRCS := server.c

$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

.Phony : all clean flean re bonus

all : $(NAME)

clean :
	$(RM) $(RMFLAGS) $(NAME)

fclean : clean

re : fclean all

bonus : all
