##
## Arcade | Graph
## Sarah-Keppler
##

CC	=	g++

RM	=	rm -rf


NAME_NCURSES	=	arcade_ncurses.so
NCURSES		=	src/NCurses.cpp				\
			./src/AGraph.cpp			\
			../Common/Error.cpp
OBJ_NCURSES	=	$(NCURSES:.cpp=.o)

NAME_SDL2	=	arcade_sdl2.so
SDL2		=	src/SDL2.cpp 				\
			./src/AGraph.cpp			\
			../Common/Error.cpp
OBJ_SDL2	=	$(SDL2:.cpp=.o)

NAME_SFML	=	arcade_sfml.so
SFML		=	src/SFML.cpp 				\
			./src/AGraph.cpp			\
			../Common/Error.cpp
OBJ_SFML	=	$(SFML:.cpp=.o)


CXXFLAGS 	+= 	-Wall -Wextra -Werror -I./include/ -fPIC

LDFLAGS		+=	-shared

all: ncurses sdl2 sfml

ncurses: $(OBJ_NCURSES)
	@$(CC) $(CXXFLAGS) $(NCURSES) $(LDFLAGS) -o $(NAME_NCURSES) -lncurses
	@mv $(NAME_NCURSES) ../lib/
	@echo -e "\033[01;38;5;44m================Compiling: NCurses\033[0;0m"

sdl2: $(OBJ_SDL2)
	@$(CC) $(CXXFLAGS) $(SDL2) $(LDFLAGS) -o $(NAME_SDL2) -lSDL2 -lSDL2_image -lSDL2_ttf
	@mv $(NAME_SDL2) ../lib/
	@echo -e "\033[01;38;5;44m================Compiling: SDL2\033[0;0m"

sfml: $(OBJ_SFML)
	@$(CC) $(CXXFLAGS) $(SFML) $(LDFLAGS) -o $(NAME_SFML) -lsfml-graphics -lsfml-system -lsfml-window
	@mv $(NAME_SFML) ../lib/
	@echo -e "\033[01;38;5;44m================Compiling: SFML\033[0;0m"

clean:
	@$(RM) *~ vgcore.* ./include/*~ ./src/*~ ./tests/*~
	@$(RM) $(OBJ_NCURSES)
	@$(RM) $(OBJ_SDL2)
	@$(RM) $(OBJ_SFML)

fclean: clean
	@$(RM) $(NAME_NCURSES)
	@$(RM) $(NAME_SDL2)
	@$(RM) $(NAME_SFML)

re: fclean all

.PHONY: all clean fclean re ncurses sdl2 sfml
