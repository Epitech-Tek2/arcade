##
## Arcade | Graph
## Sarah-Keppler
##

######### NOT TESTED #########

CC	=	g++

RM	=	rm -rf


NAME_SDL2	=	arcade_sdl2.so
SDL2		=	../src/SDL2.cpp 				\
			../src/AGraph.cpp			\
			../../Common/Error.cpp			\
			../src/main.cpp
OBJ_SDL2	=	$(SDL2:.cpp=.o)


CXXFLAGS 	+= 	-Wall -Wextra -Werror -I../include/

LDFLAGS		+=	-lSDL2 -lSDL2_image

all: sdl2

sdl2: $(OBJ_SDL2)
	@$(CC) $(CXXFLAGS) $(SDL2) $(LDFLAGS) -o $(NAME_SDL2)
	@echo -e "\033[01;38;5;44m================Compiling: SDL2\033[0;0m"

clean:
	@$(RM) *~ vgcore.* ./include/*~ ./src/*~ ./tests/*~
	@$(RM) $(OBJ_SDL2)

fclean: clean
	@$(RM) $(NAME_SDL2)

re: fclean all

.PHONY: all clean fclean re sdl2
