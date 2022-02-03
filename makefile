CC=gcc
FLAGS=-Wall -g
SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I${SDL_INC_DIR}

PROG=jeu

all: main.o initSdl.o deplacements.o
	${CC} bin/main.o bin/initSdl.o bin/deplacements.o ${LIBS} ${INCS} ${FLAGS} -o ${PROG}
main.o: src/main.c include/initSdl.h include/deplacements.h
	${CC} -c src/main.c ${LIBS} ${INCS} ${FLAGS} -o bin/main.o
initSdl.o: src/initSdl.c include/initSdl.h include/deplacements.h include/main.h
	${CC} -c src/initSdl.c ${LIBS} ${INCS} ${FLAGS} -o bin/initSdl.o
deplacements.o: src/deplacements.c include/initSdl.h include/deplacements.h
	${CC} -c src/deplacements.c ${LIBS} ${INCS} ${FLAGS} -o bin/deplacements.o

clean:
	rm -f ${PROG}
	rm -f bin/*.o
