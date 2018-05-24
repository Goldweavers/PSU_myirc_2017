CC	=	gcc

NAME	=	../../server

SRCS	=	../server.c			\
		../common/conversion.c		\
		../common/error.c		\
		../common/socket.c		\
		../common/epoll.c		\
		../common/generic_list.c	\
		../common/memory.c		\
		../common/parsing.c		\
		../common/commands.c		\
		commands/nick.c			\
		reply_codes.c			\
		user.c				\

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-I../../includes -W -Wall -Wextra -g

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: re clean fclean all
