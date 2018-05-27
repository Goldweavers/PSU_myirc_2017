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
		commands/privmsg.c		\
		commands/part.c			\
		commands/nick.c			\
		commands/quit.c			\
		commands/join.c			\
		commands/list.c			\
		commands/names.c		\
		commands/users.c		\
		reply_codes.c			\
		command.c			\
		channel.c			\
		signal.c			\
		event.c				\
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
