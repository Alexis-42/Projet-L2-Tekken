CC=gcc
FLAGS=-Wall -g -fcommon
SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
INCS=-I${SDL_INC_DIR}

SOURCE = src/main.c src/initSdl.c src/mouvements.c src/menu_principal.c src/menu_selection.c src/animations.c src/personnages.c src/joueur.c src/map.c src/gui.c src/pause.c src/menu.c src/ia.c src/options.c
PROG=jeu

${PROG}: ${SOURCE}
	${CC} -o ${PROG} ${SOURCE} ${LIBS} ${INCS} ${FLAGS}
	rm -f bin/*.o

# compile le code et les documents
all :
	${PROG}
	${docs}

# compile le code
jouer: ${PROG}
	rm -f bin/*.o
	./jeu

# compile le code avec les hitboxes
debug: ${PROG}
	rm -f bin/*.o
	./jeu debug

# compile la doc
docs:
	doxygen ./Doxyfile

# efface les .o et le programme
clean:
	rm -f ${PROG}
	rm -f bin/*.o

# efface les .o , le programme et la doc
cleanall:
	${clean}
	rm -f doc/html/search/*
	rm -f doc/latex/*

jonathan:${PROG}
	rm -f bin/*.o
	./jeu drip

