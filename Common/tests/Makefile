##
## Arcade tests
## Sarah-Keppler
##

NAME	=	err

CC	=	g++

RM	=	rm -rf

SRCS	=	../Error.cpp	\
		main.cpp

OBJS	=	 $(SRC:.cpp=.o)

CXXFLAGS += 	-Wall -Wextra -Werror -I../

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(CXXFLAGS) $(SRCS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) *~ vgcore.* *~ ../*~

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
