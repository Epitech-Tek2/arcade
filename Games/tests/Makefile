##
## Arcade tests | Game
## Sarah-Keppler
##

CC	=	g++

RM	=	rm -rf

PATH_COMMON	=	../../Common/
COMMON		=	Error.cpp

PATH_NCURSES	=	../../Graphs/src/
NCURSES		=	NCurses.cpp 			\
			AGraph.cpp			\

PATH_SDL2	=	../../Graphs/src/
SDL2		=	SDL2.cpp 			\
			AGraph.cpp			\

PATH_SFML	=	../../Graphs/src/
SFML		=	SFML.cpp 			\
			AGraph.cpp			\

NAME_NIBBLER	=	arcade_nibbler.so
NIBBLER		=	../src/Nibbler.cpp				\
			../src/AGame.cpp				\
			./main.cpp					\
			$(addprefix $(PATH_SFML), $(SFML))		\
			$(addprefix $(PATH_COMMON), $(COMMON))
OBJ_NIBBLER	=	$(NIBBLER:.cpp=.o)

			# $(addprefix $(PATH_SDL2), $(SDL2))		\
			# $(addprefix $(PATH_NCURSES), $(NCURSES))

NAME_PACMAN	=	arcade_pacman
PACMAN		=	../src/Pacman.cpp 				\
			../src/AGame.cpp 				\
			./main.cpp					\
			$(addprefix $(PATH_SFML), $(SFML))		\
			$(addprefix $(PATH_COMMON), $(COMMON))
OBJ_PACMAN	=	$(PACMAN:.cpp=.o)

CXXFLAGS 	+= 	-Wall -Wextra -Werror -I../include/

LDFLAGS		+=	 -lSDL2 -lSDL2_image -lncurses -g -lsfml-graphics -lsfml-system -lsfml-window


# -lSDL2 -lSDL2_image -lncurses -g

all: pacman

nibbler: $(OBJ_NIBBLER)
	@$(CC) $(CXXFLAGS) $(NIBBLER) $(LDFLAGS) -o $(NAME_NIBBLER)
	@echo -e "\033[01;38;5;44m================Compiling: Nibbler\033[0;0m"

pacman: $(OBJ_PACMAN)
	@$(CC) $(CXXFLAGS) $(PACMAN) $(LDFLAGS) -o $(NAME_PACMAN)
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
