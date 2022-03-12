CC=gcc
FLAGS=-Wall -g
SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
INCS=-I${SDL_INC_DIR}

SOURCE = src/main.c src/initSdl.c src/deplacements.c src/menu_principal.c src/menu_selection.c src/animations.c src/personnages.c src/joueur.c src/son.c
LOCLIB = include/animations.h include/deplacements.h include/initSdl.h include/jeu.h include/joueur.h include/menu_principal.h include/menu_selection.h include/personnages.h include/son.h
PROG=jeu

${PROG}: ${SOURCE} ${LOCLIB}
	${CC} -o ${PROG} ${SOURCE} ${LIBS} ${INCS} ${FLAGS}
	rm -f bin/*.o

jouer: ${PROG}
	./jeu
	rm -f bin/*.o

clean:
	rm -f ${PROG}
	rm -f bin/*.o
