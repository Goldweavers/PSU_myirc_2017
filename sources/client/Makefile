CC	=	gcc

NAME	=	../../client

SRCS	=	../common/error.c	\
		../common/memory.c	\
		../common/socket.c	\
		commands/server.c	\
		commands/msg.c		\
		../client.c		\
		commands.c		\
		parsing.c		\

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-I../../includes -W -Wall -Wextra

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: re clean fclean all
