##
## Arcade | Game
## Sarah-Keppler
##

CC	=	g++

RM	=	rm -rf


NAME_NIBBLER	=	arcade_nibbler.so
NIBBLER		=	src/Nibbler.cpp 			\
			src/AGame.cpp				\
			../Common/Error.cpp
OBJ_NIBBLER	=	$(NIBBLER:.cpp=.o)

NAME_PACMAN	=	arcade_pacman.so
PACMAN		=	./src/Pacman.cpp 			\
			./src/AGame.cpp				\
			../Common/Error.cpp
OBJ_PACMAN	=	$(PACMAN:.cpp=.o)


CXXFLAGS 	+= 	-Wall -Wextra -Werror -I./include/ -fPIC

LDFLAGS		+=	-shared

all: pacman nibbler

nibbler: $(OBJ_NIBBLER)
	@$(CC) $(CXXFLAGS) $(NIBBLER) $(LDFLAGS) -o $(NAME_NIBBLER)
	@mv $(NAME_NIBBLER) ../lib/
	@echo -e "\033[01;38;5;44m================Compiling: Nibbler\033[0;0m"

pacman: $(OBJ_PACMAN)
	@$(CC) $(CXXFLAGS) $(PACMAN) $(LDFLAGS) -o $(NAME_PACMAN)
	@mv $(NAME_PACMAN) ../lib/
	@echo -e "\033[01;38;5;44m================Compiling: Pacman\033[0;0m"

clean:
	@$(RM) *~ vgcore.* ./include/*~ ./src/*~ ./tests/*~
	@$(RM) $(OBJ_NIBBLER)
	@$(RM) $(OBJ_PACMAN)

fclean: clean
	@$(RM) $(NAME_NIBBLER)
	@$(RM) $(NAME_PACMAN)

re: fclean all

.PHONY: all clean fclean re nibbler pacman
