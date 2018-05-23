SRCS	=	tests/common.c			\
		sources/common/conversion.c	\
		sources/common/socket.c		\
		sources/common/error.c		\
		sources/common/generic_list.c	\

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-I./includes

LDFLAGS	=	-lcriterion --coverage

all:
	make -C "sources/client"
	make -C "sources/server"

client:
	make -C "sources/client"

server:
	make -C "sources/server"

clean:
	make clean -C "sources/client"
	make clean -C "sources/server"

fclean:	clean
	make fclean -C "sources/client"
	make fclean -C "sources/server"

tests_run:	$(OBJS)
	gcc $(OBJS) $(LDFLAGS)


re: fclean all

.PHONY: re clean fclean all
