##
## Arcade
## Sarah-Keppler
##

CC	=	g++

RM	=	rm -f

PATH_ARCADE	=	./Core/
PATH_GRAPH	=	./Graphs/
PATH_GAME	=	./Games/

all:	core graphicals games

core:
	make -sC $(PATH_ARCADE)
	@cp $(PATH_ARCADE)/arcade ./

graphicals:
	make -sC $(PATH_GRAPH)

games:
	make -sC $(PATH_GAME)

clean:
	@rm -f *~ *.vgcore
	@make -sC $(PATH_ARCADE) clean
	@make -sC $(PATH_GRAPH) clean
	@make -sC $(PATH_GAME) clean

fclean: clean
	@$(RM) *~ *vgcore.
	@$(RM) *~ arcade ./lib/*.so
	@make -sC $(PATH_ARCADE) fclean
	@make -sC $(PATH_GRAPH) fclean
	@make -sC $(PATH_GAME) fclean

re: fclean all

.PHONY: all clean fclean re core graphicals games
