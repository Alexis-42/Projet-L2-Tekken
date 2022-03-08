CC=gcc
FLAGS=-Wall -g
SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf #-lSDL2_mixer
INCS=-I${SDL_INC_DIR}

PROG=jeu

all: main.o initSdl.o deplacements.o menu_principal.o animations.o joueur.o son.o
	${CC} bin/main.o bin/initSdl.o bin/deplacements.o bin/menu_principal.o bin/animations.o bin/joueur.o bin/son.o ${LIBS} ${INCS} ${FLAGS} -o ${PROG}
main.o: src/main.c include/initSdl.h include/deplacements.h
	${CC} -c src/main.c ${LIBS} ${INCS} ${FLAGS} -o bin/main.o
initSdl.o: src/initSdl.c include/initSdl.h include/deplacements.h include/main.h include/menu_principal.h include/joueur.h include/animations.h include/jeu.h
	${CC} -c src/initSdl.c ${LIBS} ${INCS} ${FLAGS} -o bin/initSdl.o
deplacements.o: src/deplacements.c include/initSdl.h include/deplacements.h include/joueur.h include/animations.h include/jeu.h include/son.h
	${CC} -c src/deplacements.c ${LIBS} ${INCS} ${FLAGS} -o bin/deplacements.o
menu_principal.o: src/menu_principal.c include/initSdl.h include/deplacements.h
	${CC} -c src/menu_principal.c ${LIBS} ${INCS} ${FLAGS} -o bin/menu_principal.o
animations.o: src/animations.c include/animations.h include/joueur.h include/jeu.h
	${CC} -c src/animations.c ${LIBS} ${INCS} ${FLAGS} -o bin/animations.o
joueur.o: src/joueur.c include/joueur.h include/jeu.h include/animations.h
	${CC} -c src/joueur.c ${LIBS} ${INCS} ${FLAGS} -o bin/joueur.o
son.o: src/son.c
	${CC} -c src/son.c ${LIBS} ${INCS} ${FLAGS} -o bin/son.o
test: test.o
	${CC} bin/test.o ${LIBS} ${INCS} ${FLAGS} -o test1

test.o: test/test.c
	${CC} -c test/test.c ${LIBS} ${INCS} ${FLAGS} -o bin/test.o
clean:
	rm -f ${PROG}
	rm -f bin/*.o
