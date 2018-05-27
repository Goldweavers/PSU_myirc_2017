CC	=	gcc

NAME	=	../../client

SRCS	=	../common/error.c	\
		../common/memory.c	\
		../common/socket.c	\
		../common/commands.c	\
		../common/conversion.c	\
		commands/server.c	\
		commands/msg.c		\
		commands/quit.c		\
		commands/accept_file.c	\
		commands/join.c		\
		commands/list.c		\
		commands/names.c	\
		commands/users.c	\
		commands/nick.c		\
		commands/part.c		\
		../client.c		\
		commands.c		\
		../common/parsing.c	\

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
