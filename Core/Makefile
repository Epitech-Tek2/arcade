##
## Arcade
## Sarah-Keppler
##

NAME	=	arcade

CC	=	g++

RM	=	rm -rf

# MAKE 	= 	make -sC

PATH_GRAPH	=	../Graphs/src/
GRAPH		= 	AGraph.cpp

PATH_GAME	=	../Games/src/
GAME		=	AGame.cpp

PATH_CORE	=	./src/
CORE		=	Loader.cpp		\
			Score.cpp		\
			Core.cpp		\
			Menu.cpp		\
			main.cpp

PATH_COMMON	=	./../Common/
COMMON		=	Error.cpp

SRCS	=	$(addprefix $(PATH_CORE), $(CORE))	\
		$(addprefix $(PATH_GRAPH), $(GRAPH))	\
		$(addprefix $(PATH_GAME), $(GAME))	\
		$(addprefix $(PATH_COMMON), $(COMMON))

OBJS	=	 $(SRC:.cpp=.o)

CXXFLAGS += 	-Wall -Wextra -Werror -I./include/ -ldl

LDFLAGS += -ldl

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CXXFLAGS) $(SRCS) -o $(NAME) $(LDFLAGS) -g
	@echo -e "\033[01;38;5;44m================Compiling: Core\033[0;0m"

clean:
	@$(RM) *~ vgcore.* ./include/*~ ./src/*~

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re debug

debug:
	@$(CC) $(CXXFLAGS) $(SRCS) -o $(NAME) $(LDFLAGS) -g
	@echo -e "\033[01;38;5;45m============Valgrind compilation: Done\033[0;0m"
